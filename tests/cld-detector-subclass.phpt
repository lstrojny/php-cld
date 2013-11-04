--TEST--
Test subclasses CLD\Detector
--FILE--
<?php
ini_set('cld.debug', true);

echo "Override\n";
class SimpleDetector extends CLD\Detector
{}
$d = new SimpleDetector();
var_dump($d->detectLanguage('hello small world'));

class PropertyOverridingDetector extends CLD\Detector
{
	protected $includeExtendedLanguages = false;
	protected $languageHint = CLD\Language::ENGLISH;
	protected $encodingHint = CLD\Encoding::UTF8UTF8;
	protected $topLevelDomainHint = 'com';
}
echo "Property Override\n";
$d = new PropertyOverridingDetector();
var_dump($d->getIncludeExtendedLanguages());
var_dump($d->detectLanguage('hello small world'));

class MethodOverridingDetector extends CLD\Detector
{
	public function setIncludeExtendedLanguages($flag)
	{
		return parent::setIncludeExtendedLanguages($flag);
	}

	public function setLanguageHint($lang)
	{
		return parent::setLanguageHint($lang);
	}

	public function setEncodingHint($encoding)
	{
		return parent::setEncodingHint($encoding);
	}

	public function setTopLevelDomainHint($tld)
	{
		return parent::setTopLevelDomainHint($tld);
	}

	public function detectLanguage($text, $isPlainText = false)
	{
		return parent::detectLanguage($text, $isPlainText);
	}
}
echo "Method Override\n";
$d = new MethodOverridingDetector();
var_dump($d->getIncludeExtendedLanguages());
var_dump($d->setIncludeExtendedLanguages(false));
var_dump($d->getIncludeExtendedLanguages());
var_dump($d->setLanguageHint(CLD\Language::GERMAN));
var_dump($d->getLanguageHint());
var_dump($d->setEncodingHint(CLD\Encoding::UTF8UTF8));
var_dump($d->getEncodingHint());
var_dump($d->setTopLevelDomainHint('at'));
var_dump($d->getTopLevelDomainHint());
var_dump($d->detectLanguage('hallo kleine welt'));
?>
==DONE==
--EXPECT--
Override
TEXT: hello small world
PLAIN TEXT: 1
EXTENDED LANGUAGES: 1
TLD: (null)
LANGUAGE: Unknown
ENCODING: 23
array(1) {
  [0]=>
  array(5) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(19)
    ["percent"]=>
    int(94)
  }
}
Property Override
bool(false)
TEXT: hello small world
PLAIN TEXT: 1
EXTENDED LANGUAGES: 0
TLD: com
LANGUAGE: ENGLISH
ENCODING: 63
array(1) {
  [0]=>
  array(5) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(19)
    ["percent"]=>
    int(94)
  }
}
Method Override
bool(true)
NULL
bool(false)
NULL
string(2) "de"
NULL
int(63)
NULL
string(2) "at"
TEXT: hallo kleine welt
PLAIN TEXT: 0
EXTENDED LANGUAGES: 0
TLD: at
LANGUAGE: GERMAN
ENCODING: 63
array(1) {
  [0]=>
  array(5) {
    ["name"]=>
    string(6) "GERMAN"
    ["code"]=>
    string(2) "de"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(19)
    ["percent"]=>
    int(94)
  }
}
==DONE==
