/**
 * Copyright 2011, Lars Strojny <lstrojny@php.net>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this list of
 *      conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list
 *      of conditions and the following disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LARS STROJNY ''AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Lars Strojny.
 */
#include "php_cld.h"

#include <stdio.h>
#include "php.h"

#define CLD_WINDOWS
#include "encodings/public/encodings.h"
#include "encodings/compact_lang_det/compact_lang_det.h"
#include "encodings/compact_lang_det/ext_lang_enc.h"
#include "languages/internal/languages.cc"
#include "cld_encodings.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_cld_detect, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, is_plain_text)
	ZEND_ARG_INFO(0, include_extended_languages)
	ZEND_ARG_INFO(0, top_level_domain_hint)
	ZEND_ARG_INFO(0, language_hint)
	ZEND_ARG_INFO(0, encoding_hint)
ZEND_END_ARG_INFO()

static zend_class_entry *cld_language_ce;
static zend_class_entry *cld_encoding_ce;

static const zend_function_entry cld_functions[] = {
	ZEND_NS_FENTRY("CLD", detect, ZEND_FN(cld_detect), arginfo_cld_detect, 0)
	{NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(cld)
{
	int a;
	const char *code;
	zend_class_entry ce_language, ce_encoding;

	INIT_CLASS_ENTRY(ce_language, ZEND_NS_NAME("CLD", "Language"), NULL);
	cld_language_ce = zend_register_internal_class(&ce_language TSRMLS_CC);
	cld_language_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_LANGUAGES; a++) {
		if (kLanguageInfoTable[a].language_code_639_1_ != NULL) {
			code = kLanguageInfoTable[a].language_code_639_1_;
		} else if (kLanguageInfoTable[a].language_code_639_2_ != NULL) {
			code = kLanguageInfoTable[a].language_code_639_2_;
		} else {
			code = kLanguageInfoTable[a].language_code_other_;
		}
		zend_declare_class_constant_string(cld_language_ce, kLanguageInfoTable[a].language_name_, strlen(kLanguageInfoTable[a].language_name_), code TSRMLS_DC);
	}

	INIT_CLASS_ENTRY(ce_encoding, ZEND_NS_NAME("CLD", "Encoding"), NULL);
	cld_encoding_ce = zend_register_internal_class(&ce_encoding TSRMLS_CC);
	cld_encoding_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_ENCODINGS; a++) {
		zend_declare_class_constant_long(cld_encoding_ce, cld_encoding_info[a].name, strlen(cld_encoding_info[a].name), (long)cld_encoding_info[a].encoding TSRMLS_DC);
	}

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(cld)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(cld)
{
}

zend_module_entry cld_module_entry = {
	STANDARD_MODULE_HEADER,
	"cld",
	cld_functions,
	PHP_MINIT(cld),
	PHP_MSHUTDOWN(cld),
	NULL,
	NULL,
	PHP_MINFO(cld),
	CLD_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#if COMPILE_DL_CLD
ZEND_GET_MODULE(cld)
#endif

PHP_FUNCTION(cld_detect)
{
	int text_len,
		is_plain_text = 0,
		include_extended_languages = 1,
		encoding_hint = UNKNOWN_LANGUAGE,
		percentages[3],
		bytes,
		i,
		language_hint_name_len,
		top_level_domain_hint_len;

	bool reliable;

	char *text,
		*top_level_domain_hint = NULL,
		*language_hint_name = NULL;

	Language languages[3],
		language,
		language_hint;

	double normalized_score[3];

	zval *detail;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bbssl",
		&text, &text_len, &is_plain_text, &include_extended_languages,
		&top_level_domain_hint, &top_level_domain_hint_len, &language_hint_name, &language_hint_name_len, &encoding_hint) == FAILURE) {

		RETURN_NULL();
	}


	if (language_hint_name_len == 0 || language_hint_name == NULL) {
		language_hint = UNKNOWN_LANGUAGE;
	} else if (!LanguageFromCode(language_hint_name, &language_hint)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid language code given");
		RETURN_NULL();
	}


	if (encoding_hint == NULL) {
		encoding_hint = UNKNOWN_ENCODING;
	}


	if (include_extended_languages) {

		CompactLangDet::ExtDetectLanguageSummary(0, text, text_len, is_plain_text != 0,
			top_level_domain_hint, encoding_hint, language_hint,
			languages, percentages, normalized_score, &bytes, &reliable);
	} else {

		CompactLangDet::DetectLanguageSummary(0, text, text_len, is_plain_text != 0,
			top_level_domain_hint, encoding_hint, language_hint,
			languages, percentages, &bytes, &reliable);
	}

	array_init(return_value);
	for (i = 0; i < 3; i++) {
		language = languages[i];

		if (language == UNKNOWN_LANGUAGE) {
			break;
		}

		MAKE_STD_ZVAL(detail);
		array_init(detail);
		add_assoc_string(detail, "name", (char *)ExtLanguageName(language), 1);
		add_assoc_string(detail, "code", (char *)ExtLanguageCode(language), 1);
		add_assoc_bool(detail, "reliable", reliable);
		add_assoc_long(detail, "bytes", bytes);
		add_next_index_zval(return_value, detail);
	}
}
