--TEST--
CLD\Language and CLD\Encoding
--FILE--
<?php
var_dump(CLD\Language::GERMAN, CLD\Language::JAPANESE);
var_dump(CLD\Encoding::UTF8UTF8, CLD\Encoding::TAM_ELANGO);
?>
==DONE==
--EXPECTF--
string(%d) "de"
string(%d) "ja"
int(63)
int(64)
==DONE==
