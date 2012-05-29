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
  array(6) {
    ["name"]=>
    string(6) "GERMAN"
    ["code"]=>
    string(2) "de"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(46)
    ["score"]=>
    float(56.151940545004)
    ["percent"]=>
    int(100)
  }
}
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
    int(39)
    ["score"]=>
    float(31.60453808752)
    ["percent"]=>
    int(61)
  }
  [1]=>
  array(6) {
    ["name"]=>
    string(9) "NORWEGIAN"
    ["code"]=>
    string(2) "nb"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(39)
    ["score"]=>
    float(27.611044417767)
    ["percent"]=>
    int(39)
  }
}
array(2) {
  [0]=>
  array(6) {
    ["name"]=>
    string(8) "JAPANESE"
    ["code"]=>
    string(2) "ja"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(22)
    ["score"]=>
    float(49)
    ["percent"]=>
    int(63)
  }
  [1]=>
  array(6) {
    ["name"]=>
    string(7) "CHINESE"
    ["code"]=>
    string(2) "zh"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(22)
    ["score"]=>
    float(17)
    ["percent"]=>
    int(37)
  }
}
array(1) {
  [0]=>
  array(6) {
    ["name"]=>
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(32)
    ["score"]=>
    float(49.432739059968)
    ["percent"]=>
    int(100)
  }
}
==DONE==
