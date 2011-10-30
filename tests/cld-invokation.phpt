--TEST--
Test correct library invokation
--FILE--
<?php
ini_set('cld.debug', true);

var_dump(CLD\Encoding::UNKNOWN_ENCODING, CLD\Encoding::UTF8UTF8);
var_dump(CLD\Language::UNKNOWN, CLD\Language::ENGLISH);

$detector = new CLD\Detector();

CLD\detect('hallo');
$detector->detectLanguage('hallo');

CLD\detect('hallo', false);
$detector->detectLanguage('hallo', false);

CLD\detect('hallo', null);
$detector->detectLanguage('hallo', null);

CLD\detect('hallo', true, false);
$detector->setIncludeExtendedLanguages(false);
$detector->detectLanguage('hallo', true);

CLD\detect('hallo', true, false, 'com');
$detector->setTopLevelDomainHint('com');
$detector->detectLanguage('hallo', true);

CLD\detect('hallo', true, false, null, CLD\Language::ENGLISH);
$detector->setTopLevelDomainHint(null);
$detector->setLanguageHint(CLD\Language::ENGLISH);
$detector->detectLanguage('hallo');

CLD\detect('hallo', true, false, null, null, CLD\Encoding::UTF8UTF8);
$detector->setLanguageHint(null);
$detector->setEncodingHint(CLD\Encoding::UTF8UTF8);
$detector->detectLanguage('hallo');
$detector->setEncodingHint(-1);
$detector->detectLanguage('hallo');
?>
==DONE==
--EXPECT--
int(23)
int(63)
string(2) "un"
string(2) "en"
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 0
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 0
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 0
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 0
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: com
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: com
LANGUAGE: Unknown
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: ENGLISH
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: ENGLISH
ENCODING: 23
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: Unknown
ENCODING: 63
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: Unknown
ENCODING: 63
TEXT: hallo
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
==DONE==
