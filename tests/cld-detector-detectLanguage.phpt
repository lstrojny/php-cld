--TEST--
array CLD\Detector::detectLanguage(string text, bool isPlainText = true)
--FILE--
<?php
$detector = new CLD\Detector();
var_dump($detector->detectLanguage());
var_dump($detector->detectLanguage("one", "two", "three"));
var_dump($detector->detectLanguage("Das ist ein bisschen deutschsprachiger Text"));
var_dump($detector->detectLanguage("This is a little bit of english text"));

$detector->setTopLevelDomainHint('com');
$detector->setEncodingHint(CLD\Encoding::UTF8UTF8);
$detector->setLanguageHint(CLD\Language::ENGLISH);
var_dump($detector->detectLanguage("Little bit"));
?>
==DONE==
--EXPECTF--

Warning: CLD\Detector::detectLanguage() expects at least 1 parameter, 0 given in %scld-detector-detectLanguage.php on line %d
NULL

Warning: CLD\Detector::detectLanguage() expects at most 2 parameters, 3 given in %scld-detector-detectLanguage.php on line %d
NULL
array(1) {
  [0]=>
  array(4) {
    ["name"]=>
    string(6) "GERMAN"
    ["code"]=>
    string(2) "de"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(46)
  }
}
array(2) {
  [0]=>
  array(4) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(39)
  }
  [1]=>
  array(4) {
    ["name"]=>
    string(9) "NORWEGIAN"
    ["code"]=>
    string(2) "nb"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(39)
  }
}
array(1) {
  [0]=>
  array(4) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(13)
  }
}
==DONE==
