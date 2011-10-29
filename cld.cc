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

#include <ctype.h>
#define CLD_WINDOWS

#include "encodings/compact_lang_det/compact_lang_det.h"
#include "encodings/compact_lang_det/ext_lang_enc.h"
#include "base/string_util.h"
#include "cld_encodings.h"

#include "ext/standard/info.h"
#include "ext/standard/php_string.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_cld_detect, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, is_plain_text)
	ZEND_ARG_INFO(0, include_extended_languages)
	ZEND_ARG_INFO(0, top_level_domain_hint)
	ZEND_ARG_INFO(0, language_hint)
	ZEND_ARG_INFO(0, encoding_hint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_setIncludeExtendedLanguages, 1)
	ZEND_ARG_INFO(0, includeExtendedLanguages)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_setTopLevelDomainHint, 1)
	ZEND_ARG_INFO(0, topLevelDomainHint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_setLanguageHint, 1)
	ZEND_ARG_INFO(0, languageHint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_setEncodingHint, 1)
	ZEND_ARG_INFO(0, encodingHint)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_cld_detector_detect, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, isPlainText)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_get, 0)
ZEND_END_ARG_INFO()

static zend_class_entry *cld_language_ce;
static zend_class_entry *cld_encoding_ce;
static zend_class_entry *cld_detector_ce;

static zend_function_entry cld_detector_methods[] = {
	PHP_ME(cld_detector, setIncludeExtendedLanguages,	arginfo_cld_detector_setIncludeExtendedLanguages,	ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getIncludeExtendedLanguages,	arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setTopLevelDomainHint,		arginfo_cld_detector_setTopLevelDomainHint,			ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getTopLevelDomainHint,		arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setLanguageHint,				arginfo_cld_detector_setLanguageHint,				ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getLanguageHint,				arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setEncodingHint,				arginfo_cld_detector_setEncodingHint,				ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getEncodingHint,				arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, detect,						arginfo_cld_detector_detect,						ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

static const zend_function_entry cld_functions[] = {
	ZEND_NS_FENTRY("CLD", detect, ZEND_FN(cld_detect), arginfo_cld_detect, 0)
	{NULL, NULL, NULL}
};

char *cld_strtoupper(char *s, size_t len)
{
	unsigned char *c, *e;

	c = (unsigned char *)s;
	e = (unsigned char *)c+len;

	while (c < e) {
		*c = toupper(*c);
		c++;
	}
	return s;
}

PHP_MINIT_FUNCTION(cld)
{
	int a;

	zend_class_entry ce_language,
		ce_encoding,
		ce_detector;

	INIT_CLASS_ENTRY(ce_detector, ZEND_NS_NAME("CLD", "Detector"), cld_detector_methods);
	cld_detector_ce = zend_register_internal_class(&ce_detector TSRMLS_CC);
	zend_declare_property_bool(cld_detector_ce, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, FALSE, ZEND_ACC_PROTECTED TSRMLS_CC);

	INIT_CLASS_ENTRY(ce_language, ZEND_NS_NAME("CLD", "Language"), NULL);
	cld_language_ce = zend_register_internal_class(&ce_language TSRMLS_CC);
	cld_language_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_LANGUAGES; a++) {
		size_t constant_name_len;
		const char *code;
		char *constant_name;

		code = LanguageCode((Language) a);
		constant_name = (char*)LanguageName((Language) a);
		constant_name_len = strlen(constant_name);
		constant_name = estrndup(constant_name, constant_name_len);
		cld_strtoupper(constant_name, constant_name_len);
		zend_declare_class_constant_string(cld_language_ce, constant_name, constant_name_len, code TSRMLS_CC);

		efree(constant_name);
	}

	INIT_CLASS_ENTRY(ce_encoding, ZEND_NS_NAME("CLD", "Encoding"), NULL);
	cld_encoding_ce = zend_register_internal_class(&ce_encoding TSRMLS_CC);
	cld_encoding_ce->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_ENCODINGS; a++) {
		zend_declare_class_constant_long((zend_class_entry *)cld_encoding_ce,  (const char *)cld_encoding_info[a].name, (size_t)strlen(cld_encoding_info[a].name), (long)cld_encoding_info[a].encoding TSRMLS_CC);
	}

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
	NULL,
	NULL,
	NULL,
	PHP_MINFO(cld),
	CLD_VERSION,
	STANDARD_MODULE_PROPERTIES
};

extern "C" {
#if COMPILE_DL_CLD
ZEND_GET_MODULE(cld)
#endif
}

PHP_FUNCTION(cld_detect)
{
	int is_plain_text = 0,
		include_extended_languages = 1,
		encoding_hint = UNKNOWN_LANGUAGE,
		percentages[3],
		bytes,
		i,
		text_len,
		language_hint_name_len,
		top_level_domain_hint_len,
		language_name_len;

	bool reliable;

	char *text,
		*language_name,
		*top_level_domain_hint = NULL,
		*language_hint_name = NULL;

	Language languages[3],
		language,
		language_hint;

	double normalized_score;

	zval *detail;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bbssl",
		&text, &text_len, &is_plain_text, &include_extended_languages,
		&top_level_domain_hint, &top_level_domain_hint_len, &language_hint_name, &language_hint_name_len, &encoding_hint) == FAILURE) {

		RETURN_NULL();
	}


	if (language_hint_name_len == 0 || language_hint_name == NULL) {
		language_hint = UNKNOWN_LANGUAGE;
	} else if (!LanguageFromCode(language_hint_name, &language_hint)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid language code \"%s\"", language_hint_name);
		RETURN_NULL();
	}


	if (encoding_hint == NULL) {
		encoding_hint = UNKNOWN_ENCODING;
	}


	CompactLangDet::DetectLanguage(0, text, text_len, is_plain_text,
		include_extended_languages, 1, 0, top_level_domain_hint, encoding_hint,
		language_hint, languages, percentages, &normalized_score, &bytes, &reliable);


	array_init(return_value);
	for (i = 0; i < 3; i++) {
		language = languages[i];

		if (language == UNKNOWN_LANGUAGE) {
			break;
		}

		MAKE_STD_ZVAL(detail);
		array_init(detail);
		language_name = (char *)ExtLanguageName(language);
		language_name_len = strlen(language_name);
		language_name = estrndup(language_name, language_name_len);
		cld_strtoupper(language_name, language_name_len);
		add_assoc_string(detail, "name", language_name, 0);
		add_assoc_string(detail, "code", (char *)ExtLanguageCode(language), 1);
		add_assoc_bool(detail, "reliable", reliable);
		add_assoc_long(detail, "bytes", bytes);
		add_next_index_zval(return_value, detail);
	}
}

PHP_METHOD(cld_detector, setIncludeExtendedLanguages)
{
	zval *obj;

	int include;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &obj, cld_detector_ce, &include) == FAILURE) {
		RETURN_NULL();
	}

	zend_update_property_bool(cld_detector_ce, obj, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, include TSRMLS_CC);
}

PHP_METHOD(cld_detector, getIncludeExtendedLanguages)
{
	zval *obj, *include;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &obj, cld_detector_ce) == FAILURE) {
		RETURN_NULL();
	}

	include = zend_read_property(cld_detector_ce, obj, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, 0 TSRMLS_CC);
	RETVAL_ZVAL(include, 1, 0);
}

PHP_METHOD(cld_detector, setTopLevelDomainHint)
{}

PHP_METHOD(cld_detector, getTopLevelDomainHint)
{}

PHP_METHOD(cld_detector, setLanguageHint)
{}

PHP_METHOD(cld_detector, getLanguageHint)
{}

PHP_METHOD(cld_detector, setEncodingHint)
{}

PHP_METHOD(cld_detector, getEncodingHint)
{}

PHP_METHOD(cld_detector, detect)
{}
