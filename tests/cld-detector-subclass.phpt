--TEST--
Test subclasses CLD\Detector
--FILE--
<?php
ini_set('cld.debug', true);

class SimpleDetector extends CLD\Detector
{}
$d = new SimpleDetector();
var_dump($d->detectLanguage('hello'));

class PropertyOverridingDetector extends CLD\Detector
{
	protected $includeExtendedLanguages = false;
	protected $languageHint = CLD\Language::ENGLISH;
	protected $encodingHint = CLD\Encoding::UTF8UTF8;
	protected $topLevelDomainHint = 'com';
}
$d = new PropertyOverridingDetector();
var_dump($d->detectLanguage('hello'));

class MethodOverridingDetector extends CLD\Detector
{
	public function setIncludeExtendedLanguages($flag)
	{
		parent::setIncludeExtendedLanguages($flag);
	}

	public function setLanguageHint($lang)
	{
		parent::setLanguageHint($lang);
	}

	public function setEncodingHint($encoding)
	{
		parent::setEncodingHint($encoding);
	}

	public function setTopLevelDomainHint($tld)
	{
		parent::setTopLevelDomainHint($tld);
	}

	public function detectLanguage($text, $isPlainText = false)
	{
		return parent::detectLanguage($text, $isPlainText);
	}
}
$d = new MethodOverridingDetector();
var_dump($d->setIncludeExtendedLanguages(false));
var_dump($d->getIncludeExtendedLanguages());
var_dump($d->setLanguageHint(CLD\Language::GERMAN));
var_dump($d->getLanguageHint());
var_dump($d->setEncodingHint(CLD\Encoding::UTF8UTF8));
var_dump($d->getEncodingHint());
var_dump($d->setTopLevelDomainHint('at'));
var_dump($d->getTopLevelDomainHint());
var_dump($d->detectLanguage('hallo'));
?>
==DONE==
--EXPECT--
TEXT: hello
PLAIN TEXT: 1
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
array(2) {
  [0]=>
  array(6) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(4.0518638573744)
    ["percent"]=>
    int(62)
  }
  [1]=>
  array(6) {
    ["name"]=>
    string(7) "ITALIAN"
    ["code"]=>
    string(2) "it"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(4.6189376443418)
    ["percent"]=>
    int(38)
  }
}
TEXT: hello
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: com
LANGUAGE: ENGLISH
ENCODING: 63
array(2) {
  [0]=>
  array(6) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(4.0518638573744)
    ["percent"]=>
    int(62)
  }
  [1]=>
  array(6) {
    ["name"]=>
    string(7) "ITALIAN"
    ["code"]=>
    string(2) "it"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(4.6189376443418)
    ["percent"]=>
    int(38)
  }
}
NULL
bool(false)
NULL
string(2) "de"
NULL
int(63)
NULL
string(2) "at"
TEXT: hallo
PLAIN TEXT: 0
EXTENDED LANGUAGES: 0
TLD: at
LANGUAGE: GERMAN
ENCODING: 63
array(2) {
  [0]=>
  array(6) {
    ["name"]=>
    string(6) "GERMAN"
    ["code"]=>
    string(2) "de"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(12.386457473163)
    ["percent"]=>
    int(62)
  }
  [1]=>
  array(6) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(8)
    ["score"]=>
    float(4.0518638573744)
    ["percent"]=>
    int(38)
  }
}
==DONE==
