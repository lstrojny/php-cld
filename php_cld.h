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
#ifndef PHP_CLD_H
#define PHP_CLD_H
#define CLD_VERSION "0.6.0-dev"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef PHP_WIN32
# define PHP_CLD_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_CLD_API __attribute__ ((visibility("default")))
#else
# define PHP_CLD_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"

#ifdef __cplusplus
} /* extern C */
#endif

extern zend_module_entry cld_module_entry;
#define phpext_cld_ptr &cld_module_entry

PHP_MINIT_FUNCTION(cld);
PHP_MSHUTDOWN_FUNCTION(cld);
PHP_MINFO_FUNCTION(cld);

PHP_FUNCTION(cld_detect);

PHP_METHOD(cld_detector, setIncludeExtendedLanguages);
PHP_METHOD(cld_detector, getIncludeExtendedLanguages);
PHP_METHOD(cld_detector, setTopLevelDomainHint);
PHP_METHOD(cld_detector, getTopLevelDomainHint);
PHP_METHOD(cld_detector, setLanguageHint);
PHP_METHOD(cld_detector, getLanguageHint);
PHP_METHOD(cld_detector, setEncodingHint);
PHP_METHOD(cld_detector, getEncodingHint);
PHP_METHOD(cld_detector, detectLanguage);

#ifdef PHP_WIN32
# ifndef __BOOL_DEFINED
typedef int bool
# endif
# define _ALLOW_KEYWORD_MACROS
#endif

PHP_CLD_API char *cld_strtoupper(char *s, size_t len);
PHP_CLD_API char *cld_strtolower(char *s, size_t len);
PHP_CLD_API int cld_detect_language(zval **result, const char *text, int text_len, bool is_plain_text, zend_bool include_extended_languages, const char *top_level_domain_hint, int top_level_domain_hint_len, char *language_hint_name, int language_hint_name_len, long encoding_hint TSRMLS_DC);

ZEND_BEGIN_MODULE_GLOBALS(cld)
	int debug;
ZEND_END_MODULE_GLOBALS(cld)

PHP_CLD_API ZEND_EXTERN_MODULE_GLOBALS(cld)
static void cld_init_globals(zend_cld_globals *cld_globals);

#ifdef ZTS
#define CLDG(v) TSRMG(cld_globals_id, zend_cld_globals *, v)
#else
#define CLDG(v) (cld_globals.v)
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#endif
