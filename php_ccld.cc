/**
 * Copyright (C) 2011 by Lars Strojny <lstrojny@php.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "php_ccld.h"

#include <stdio.h>
#include "php.h"

#define CLD_WINDOWS
#include "encodings/compact_lang_det/compact_lang_det.h"
#include "encodings/compact_lang_det/ext_lang_enc.h"
#include "encodings/proto/encodings.pb.h"


ZEND_BEGIN_ARG_INFO(arginfo_ccld_detect, 1)
	ZEND_ARG_INFO(0, text)
	ZEND_ARG_INFO(0, is_plain_text)
	ZEND_ARG_INFO(0, include_extended_languages)
	ZEND_ARG_INFO(0, top_level_domain_hint)
	ZEND_ARG_INFO(0, language_hint)
	ZEND_ARG_INFO(0, encoding_hint)
ZEND_END_ARG_INFO()

static const zend_function_entry ccld_functions[] = {
	ZEND_NS_FENTRY("CCLD", detect, ZEND_FN(ccld_detect), arginfo_ccld_detect, 0)
	{NULL, NULL, NULL}
};


PHP_MINIT_FUNCTION(ccld)
{
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(ccld)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(ccld)
{
}

zend_module_entry ccld_module_entry = {
	STANDARD_MODULE_HEADER,
	"ccld",
	ccld_functions,
	PHP_MINIT(ccld),
	PHP_MSHUTDOWN(ccld),
	NULL,
	NULL,
	PHP_MINFO(ccld),
	CCLD_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#if COMPILE_DL_CCLD
ZEND_GET_MODULE(ccld)
#endif

PHP_FUNCTION(ccld_detect)
{
	char *text;

	int text_len,
		is_plain_text = 0,
		include_extended_languages = 1,
		encoding_hint,
		percentages[3],
		bytes,
        i,
        len;

	bool reliable;

	char *top_level_domain_hint = NULL,
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
		CompactLangDet::ExtDetectLanguageSummary(0, text, text_len, is_plain_text != 0, top_level_domain_hint, encoding_hint, language_hint, languages, percentages, normalized_score, &bytes, &reliable);
	} else {
		CompactLangDet::DetectLanguageSummary(0, text, text_len, is_plain_text != 0, top_level_domain_hint, encoding_hint, language_hint, languages, percentages, &bytes, &reliable);
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
