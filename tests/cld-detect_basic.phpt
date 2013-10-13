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
    string(7) "ENGLISH"
    ["code"]=>
    string(2) "en"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(12)
    ["percent"]=>
    int(91)
  }
}
==DONE==
