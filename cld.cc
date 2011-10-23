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
#include "encodings/proto/encodings.pb.h"


ZEND_BEGIN_ARG_INFO_EX(arginfo_cld_detect, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, is_plain_text)
	ZEND_ARG_INFO(0, include_extended_languages)
	ZEND_ARG_INFO(0, top_level_domain_hint)
	ZEND_ARG_INFO(0, language_hint)
	ZEND_ARG_INFO(0, encoding_hint)
ZEND_END_ARG_INFO()

static const zend_function_entry cld_functions[] = {
	ZEND_NS_FENTRY("CLD", detect, ZEND_FN(cld_detect), arginfo_cld_detect, 0)
	{NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(cld)
{
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
		encoding_hint,
		percentages[3],
		bytes,
		i,
		len;

	bool reliable;

	char *text,
		*top_level_domain_hint = NULL,
		*language_hint_name = NULL,
		*encoding_hint_name = NULL;

	Language languages[3],
		language,
		language_hint;

	double normalized_score[3];

	zval *detail;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bbsss",
		&text, &text_len, &is_plain_text, &include_extended_languages,
		&top_level_domain_hint, &len, &language_hint_name, &len, &encoding_hint_name, &len) == FAILURE) {

		RETURN_NULL();
	}


	if (language_hint_name == NULL) {
		language_hint = UNKNOWN_LANGUAGE;
	} else if (!LanguageFromCode(language_hint_name, &language_hint)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid language code given");
		RETURN_NULL();
	}


	if (encoding_hint_name == NULL) {
		encoding_hint = UNKNOWN_ENCODING;
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Encoding hint not implemented");
		RETURN_NULL();
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
