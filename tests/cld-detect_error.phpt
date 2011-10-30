--TEST--
CLD\detect() error behavior
--FILE--
<?php
var_dump(CLD\detect());
var_dump(CLD\detect("text", true, true, ".com", "invalid language code"));
var_dump(CLD\detect("text", true, true, ".com", "en", 10000));
var_dump(CLD\detect("text", true, true, ".com", "en", -2));
?>
==DONE==
--EXPECTF--

Warning: CLD\detect() expects at least 1 parameter, 0 given in %s.php on line %d
NULL

Warning: CLD\detect(): Invalid language code "invalid language code" in %s.php on line %d
NULL

Warning: CLD\detect(): Invalid encoding "10000" in %s.php on line %d
NULL

Warning: CLD\detect(): Invalid encoding "-2" in %s.php on line %d
NULL
==DONE==
