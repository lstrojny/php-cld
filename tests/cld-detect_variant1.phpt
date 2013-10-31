--TEST--
CLD\detect() basic behavior
--FILE--
<?php
var_dump(CLD\detect("Das ist ein bisschen deutschsprachiger Text", true));
var_dump(CLD\detect("This is a little bit of english text", false, true, '.no', CLD\Language::NORWEGIAN));
var_dump(CLD\detect("日[の]本([の]国", false, true, null, null, CLD\Encoding::JAPANESE_EUC_JP));
var_dump(CLD\detect("<a>Hello world, how are you today</a>", false, true));
?>
==DONE==
--EXPECT--
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
    int(45)
    ["percent"]=>
    int(97)
  }
}
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
    int(38)
    ["percent"]=>
    int(97)
  }
}
array(1) {
  [0]=>
  array(5) {
    ["name"]=>
    string(8) "JAPANESE"
    ["code"]=>
    string(2) "ja"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(21)
    ["percent"]=>
    int(95)
  }
}
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
    int(31)
    ["percent"]=>
    int(96)
  }
}
==DONE==
