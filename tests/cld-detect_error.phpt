--TEST--
CLD\detect() error behavior
--FILE--
<?php
var_dump(CLD\detect());
var_dump(CLD\detect("text", true, true, ".com", "invalid language code"));
var_dump(CLD\detect("text", true, true, ".com", "de", "encoding"));
?>
==DONE==
--EXPECTF--

Warning: CLD\detect() expects at least 1 parameter, 0 given in %s.php on line %d
NULL

Warning: CLD\detect(): Invalid language code given in %s.php on line %d
NULL

Warning: CLD\detect(): Encoding hint not implemented in %s.php on line %d
NULL
==DONE==
