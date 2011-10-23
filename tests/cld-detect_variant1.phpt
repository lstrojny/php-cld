--TEST--
CLD\detect() basic behavior
--FILE--
<?php
var_dump(CLD\detect("Das ist ein bisschen deutschsprachiger Text", true));
var_dump(CLD\detect("This is a little bit of english text", false, true, '.no', 'nor'));
var_dump(CLD\detect("<a>Hello world, how are you today</a>", false, true));
?>
==DONE==
--EXPECT--
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
    int(32)
  }
}
==DONE==
