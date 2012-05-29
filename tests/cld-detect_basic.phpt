--TEST--
CLD\detect() basic behavior
--FILE--
<?php
var_dump(CLD\detect("Das ist ein bisschen deutschsprachiger Text"));
var_dump(CLD\detect("This is a little bit of english text"));
var_dump(CLD\detect("Little bit"));
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
    float(9.6038415366146)
    ["percent"]=>
    int(39)
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
    int(13)
    ["score"]=>
    float(12.155591572123)
    ["percent"]=>
    int(100)
  }
}
==DONE==
