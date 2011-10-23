--TEST--
CLD\Language and CLD\Encoding
--FILE--
<?php
var_dump(CLD\Language::GERMAN);
var_dump(CLD\ENCODING::UTF8UTF8);
?>
==DONE==
--EXPECTF--
string(%d) "de"
int(%d)
==DONE==
