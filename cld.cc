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
#include "Zend/zend_exceptions.h"
#include "spl/spl_exceptions.h"

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

ZEND_BEGIN_ARG_INFO_EX(arginfo_cld_detector_detectLanguage, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, isPlainText)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cld_detector_get, 0)
ZEND_END_ARG_INFO()

PHP_INI_BEGIN()
	STD_PHP_INI_BOOLEAN("cld.debug", "0", PHP_INI_ALL, OnUpdateBool, debug, zend_cld_globals, cld_globals)
PHP_INI_END()

static zend_class_entry *cld_ce_Language;
static zend_class_entry *cld_ce_Encoding;
static zend_class_entry *cld_ce_Detector;
static zend_class_entry *cld_ce_InvalidArgumentException;
static zend_class_entry *cld_ce_InvalidLanguageException;
static zend_class_entry *cld_ce_InvalidEncodingException;

static zend_function_entry cld_detector_methods[] = {
	PHP_ME(cld_detector, setIncludeExtendedLanguages,	arginfo_cld_detector_setIncludeExtendedLanguages,	ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getIncludeExtendedLanguages,	arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setTopLevelDomainHint,			arginfo_cld_detector_setTopLevelDomainHint,			ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getTopLevelDomainHint,			arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setLanguageHint,				arginfo_cld_detector_setLanguageHint,				ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getLanguageHint,				arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, setEncodingHint,				arginfo_cld_detector_setEncodingHint,				ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, getEncodingHint,				arginfo_cld_detector_get,							ZEND_ACC_PUBLIC)
	PHP_ME(cld_detector, detectLanguage,				arginfo_cld_detector_detectLanguage,				ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

ZEND_DECLARE_MODULE_GLOBALS(cld)

static const zend_function_entry cld_functions[] = {
	ZEND_NS_FENTRY("CLD", detect, ZEND_FN(cld_detect), arginfo_cld_detect, 0)
	{NULL, NULL, NULL}
};

PHPAPI char *cld_strtoupper(char *s, size_t len)
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

PHPAPI char *cld_strtolower(char *s, size_t len)
{
	unsigned char *c, *e;

	c = (unsigned char *)s;
	e = (unsigned char *)c+len;

	while (c < e) {
		*c = tolower(*c);
		c++;
	}
	return s;
}

PHPAPI int cld_detect_language(zval **result, char *text, int text_len, int is_plain_text, int include_extended_languages, char *top_level_domain_hint, int top_level_domain_hint_len, char *language_hint_name, int language_hint_name_len, long encoding_hint TSRMLS_DC)
{
	int percentages[3],
		bytes,
		language_name_len,
		i;

	bool reliable;

	Language languages[3],
		language,
		language_hint;

	char *language_name;

	double normalized_scores[3];

	zval *detail;

	if (language_hint_name_len == 0 || language_hint_name == NULL) {
		language_hint = UNKNOWN_LANGUAGE;
	} else if (!LanguageFromCode(language_hint_name, &language_hint)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid language code \"%s\"", language_hint_name);
		return FAILURE;
	}


	if (encoding_hint == -1) {
		encoding_hint = UNKNOWN_ENCODING;
	} else if (encoding_hint < 0 || encoding_hint > NUM_ENCODINGS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid encoding \"%d\"", (int) encoding_hint);
		return FAILURE;
	}


	if (CLDG(debug)) {
		php_printf("TEXT: %s\n", text);
		php_printf("PLAIN TEXT: %d\n", is_plain_text);
		php_printf("EXTENDED LANGUAGES: %d\n", include_extended_languages);
		php_printf("TLD: %s\n", top_level_domain_hint);
		php_printf("LANGUAGE: %s\n", LanguageName(language_hint));
		php_printf("ENCODING: %d\n", (int)encoding_hint);
	}


	CompactLangDet::DetectLanguage(0, text, text_len, is_plain_text,
		include_extended_languages, 1, 0, top_level_domain_hint, encoding_hint,
		language_hint, languages, percentages, normalized_scores, &bytes, &reliable);


	array_init(*result);
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
		add_assoc_double(detail, "score", normalized_scores[i]);
		add_assoc_long(detail, "percent", percentages[i]);
		add_next_index_zval(*result, detail);
	}

	return SUCCESS;
}

PHP_MINIT_FUNCTION(cld)
{
	int a;

	zend_class_entry ce_Language,
		ce_Encoding,
		ce_Detector,
		ce_InvalidArgumentException,
		ce_InvalidLanguageException,
		ce_InvalidEncodingException;

	INIT_NS_CLASS_ENTRY(ce_Detector, "CLD", "Detector", cld_detector_methods);
	cld_ce_Detector = zend_register_internal_class(&ce_Detector TSRMLS_CC);
	zend_declare_property_bool(cld_ce_Detector, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, TRUE, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(cld_ce_Detector, "topLevelDomainHint", sizeof("topLevelDomainHint")-1, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(cld_ce_Detector, "languageHint", sizeof("languageHint")-1, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(cld_ce_Detector, "encodingHint", sizeof("encodingHint")-1, -1, ZEND_ACC_PROTECTED TSRMLS_CC);

	INIT_NS_CLASS_ENTRY(ce_InvalidArgumentException, "CLD", "InvalidArgumentException", NULL);
	cld_ce_InvalidArgumentException = zend_register_internal_class_ex(&ce_InvalidArgumentException, spl_ce_InvalidArgumentException, NULL TSRMLS_CC);
	cld_ce_InvalidArgumentException->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

	INIT_NS_CLASS_ENTRY(ce_InvalidLanguageException, "CLD", "InvalidLanguageException", NULL);
	cld_ce_InvalidLanguageException = zend_register_internal_class_ex(&ce_InvalidLanguageException, cld_ce_InvalidArgumentException, NULL TSRMLS_CC);

	INIT_NS_CLASS_ENTRY(ce_InvalidEncodingException, "CLD", "InvalidEncodingException", NULL);
	cld_ce_InvalidEncodingException = zend_register_internal_class_ex(&ce_InvalidEncodingException, cld_ce_InvalidArgumentException, NULL TSRMLS_CC);

	INIT_NS_CLASS_ENTRY(ce_Language, "CLD", "Language", NULL);
	cld_ce_Language = zend_register_internal_class(&ce_Language TSRMLS_CC);
	cld_ce_Language->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_LANGUAGES; a++) {
		size_t constant_name_len;
		const char *code;
		char *constant_name;

		code = LanguageCode((Language) a);
		constant_name = (char*)LanguageName((Language) a);
		constant_name_len = strlen(constant_name);
		constant_name = estrndup(constant_name, constant_name_len);
		cld_strtoupper(constant_name, constant_name_len);
		zend_declare_class_constant_string(cld_ce_Language, constant_name, constant_name_len, code TSRMLS_CC);

		efree(constant_name);
	}


	INIT_NS_CLASS_ENTRY(ce_Encoding, "CLD", "Encoding", NULL);
	cld_ce_Encoding = zend_register_internal_class(&ce_Encoding TSRMLS_CC);
	cld_ce_Encoding->ce_flags |= ZEND_ACC_FINAL_CLASS;

	for (a = 0; a < NUM_ENCODINGS; a++) {
		zend_declare_class_constant_long((zend_class_entry *)cld_ce_Encoding,  (const char *)cld_encoding_info[a].name, (size_t)strlen(cld_encoding_info[a].name), (long)cld_encoding_info[a].encoding TSRMLS_CC);
	}


	ZEND_INIT_MODULE_GLOBALS(cld, cld_init_globals,	NULL);
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}

static void cld_init_globals(zend_cld_globals *cld_globals)
{
	cld_globals->debug = 0;
}

PHP_MSHUTDOWN_FUNCTION(cld)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

PHP_MINFO_FUNCTION(cld)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "CLD (Chromium Language Detector) support", "enabled");

	DISPLAY_INI_ENTRIES();

	php_info_print_table_end();
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

extern "C" {
#if COMPILE_DL_CLD
ZEND_GET_MODULE(cld)
#endif
}

PHP_FUNCTION(cld_detect)
{
	int is_plain_text = 1,
		include_extended_languages = 1,
		top_level_domain_hint_len = 0,
		language_hint_name_len = 0,
		text_len;

	long encoding_hint = -1;

	char *text,
		*top_level_domain_hint = NULL,
		*language_hint_name = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|bbssl", &text, &text_len, &is_plain_text, &include_extended_languages, &top_level_domain_hint, &top_level_domain_hint_len, &language_hint_name, &language_hint_name_len, &encoding_hint) == FAILURE) {
		RETURN_NULL();
	}

	if (top_level_domain_hint_len == 0) {
		top_level_domain_hint = NULL;
	}

	if (cld_detect_language(&return_value, text, text_len, is_plain_text, include_extended_languages, top_level_domain_hint, top_level_domain_hint_len, language_hint_name, language_hint_name_len, encoding_hint TSRMLS_CC) == FAILURE) {
		RETURN_NULL();
	}
}



PHP_METHOD(cld_detector, setIncludeExtendedLanguages)
{
	zval *obj;

	int include;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &obj, cld_ce_Detector, &include) == FAILURE) {
		RETURN_NULL();
	}

	zend_update_property_bool(cld_ce_Detector, obj, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, include TSRMLS_CC);
}

PHP_METHOD(cld_detector, getIncludeExtendedLanguages)
{
	zval *obj,
		*include;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &obj, cld_ce_Detector) == FAILURE) {
		RETURN_NULL();
	}

	include = zend_read_property(cld_ce_Detector, obj, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, 0 TSRMLS_CC);
	RETVAL_ZVAL(include, 1, 0);
}

PHP_METHOD(cld_detector, setTopLevelDomainHint)
{
	zval *obj;
	char *hint;
	int len;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &obj, cld_ce_Detector, &hint, &len) == FAILURE) {
		RETURN_NULL();
	}

	if (len > 0) {
		zend_update_property_stringl(cld_ce_Detector, obj, "topLevelDomainHint", sizeof("topLevelDomainHint")-1, hint, len TSRMLS_CC);
	} else {
		zend_update_property_null(cld_ce_Detector, obj, "topLevelDomainHint", sizeof("topLevelDomainHint")-1 TSRMLS_CC);
	}
}

PHP_METHOD(cld_detector, getTopLevelDomainHint)
{
	zval *obj,
		*hint;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &obj, cld_ce_Detector)) {
		RETURN_NULL();
	}

	hint = zend_read_property(cld_ce_Detector, obj, "topLevelDomainHint", sizeof("topLevelDomainHint")-1, 0 TSRMLS_CC);
	RETVAL_ZVAL(hint, 1, 0);
}

PHP_METHOD(cld_detector, setLanguageHint)
{
	zval *obj;
	char *hint;
	int len;
	Language lang;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &obj, cld_ce_Detector, &hint, &len) == FAILURE) {
		RETURN_NULL();
	}


	if (len > 0) {

		hint = estrndup(hint, len);
		cld_strtolower(hint, len);

		if (!LanguageFromCode(hint, &lang)) {
			zend_throw_exception_ex(cld_ce_InvalidLanguageException, 100 TSRMLS_CC, "Invalid language code \"%s\"", hint TSRMLS_CC);
		} else {
			zend_update_property_stringl(cld_ce_Detector, obj, "languageHint", sizeof("languageHint")-1, hint, len TSRMLS_CC);
		}

		efree(hint);
	} else {
		zend_update_property_null(cld_ce_Detector, obj, "languageHint", sizeof("languageHint")-1 TSRMLS_CC);
	}
}

PHP_METHOD(cld_detector, getLanguageHint)
{
	zval *obj,
		*hint;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &obj, cld_ce_Detector)) {
		RETURN_NULL();
	}

	hint = zend_read_property(cld_ce_Detector, obj, "languageHint", sizeof("languageHint")-1, 0 TSRMLS_CC);
	RETVAL_ZVAL(hint, 1, 0);
}

PHP_METHOD(cld_detector, setEncodingHint)
{
	zval *obj;
	long hint;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &obj, cld_ce_Detector, &hint) == FAILURE) {
		RETURN_NULL();
	}


	if (hint == -1) {
		zend_update_property_long(cld_ce_Detector, obj, "encodingHint", sizeof("encodingHint")-1, -1 TSRMLS_CC);
	} else if (hint < 0 || hint > NUM_ENCODINGS) {
		zend_throw_exception_ex(cld_ce_InvalidEncodingException, 100 TSRMLS_CC, "Invalid encoding \"%d\"", hint TSRMLS_CC);
		RETURN_NULL();
	}

	zend_update_property_long(cld_ce_Detector, obj, "encodingHint", sizeof("encodingHint")-1, hint TSRMLS_CC);
}

PHP_METHOD(cld_detector, getEncodingHint)
{
	zval *obj,
		*hint;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &obj, cld_ce_Detector) == FAILURE) {
		RETURN_NULL();
	}

	hint = zend_read_property(cld_ce_Detector, obj, "encodingHint", sizeof("encodingHint")-1, 0 TSRMLS_CC);
	RETVAL_ZVAL(hint, 1, 0);
}

PHP_METHOD(cld_detector, detectLanguage)
{
	zval *obj,
		*val;

	char *text,
		*top_level_domain_hint = NULL,
		*language_hint_name;

	int text_len,
		is_plain_text = 1,
		include_extended_languages,
		top_level_domain_hint_len,
		language_hint_name_len;

	long encoding_hint;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os|b", &obj, cld_ce_Detector, &text, &text_len, &is_plain_text) == FAILURE) {
		RETURN_NULL();
	}

	val = zend_read_property(cld_ce_Detector, obj, "includeExtendedLanguages", sizeof("includeExtendedLanguages")-1, 0 TSRMLS_CC);
	include_extended_languages = Z_BVAL_P(val);

	val = zend_read_property(cld_ce_Detector, obj, "topLevelDomainHint", sizeof("topLevelDomainHint")-1, 0 TSRMLS_CC);
	if (ZVAL_IS_NULL(val)) {
		top_level_domain_hint = NULL;
		top_level_domain_hint_len = 0;
	} else {
		top_level_domain_hint = Z_STRVAL_P(val);
		top_level_domain_hint_len = Z_STRLEN_P(val);
	}

	val = zend_read_property(cld_ce_Detector, obj, "languageHint", sizeof("languageHint")-1, 0 TSRMLS_CC);
	if (ZVAL_IS_NULL(val)) {
		language_hint_name = NULL;
		language_hint_name_len = 0;
	} else {
		language_hint_name = Z_STRVAL_P(val);
		language_hint_name_len = Z_STRLEN_P(val);
	}

	val = zend_read_property(cld_ce_Detector, obj, "encodingHint", sizeof("encodingHint")-1, 0 TSRMLS_CC);
	encoding_hint = Z_LVAL_P(val);

	if (cld_detect_language(&return_value, text, text_len, is_plain_text, include_extended_languages, top_level_domain_hint, top_level_domain_hint_len, language_hint_name, language_hint_name_len, encoding_hint TSRMLS_CC) == FAILURE) {
		RETURN_NULL();
	}
}
