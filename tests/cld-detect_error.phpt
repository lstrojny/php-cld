--TEST--
CLD\detect() error behavior
--FILE--
<?php
var_dump(CLD\detect());
var_dump(CLD\detect("text", true, true, ".com", "invalid language code"));
?>
==DONE==
--EXPECTF--

Warning: CLD\detect() expects at least 1 parameter, 0 given in %s.php on line %d
NULL

Warning: CLD\detect(): Invalid language code "invalid language code" in %s.php on line %d
NULL
==DONE==
