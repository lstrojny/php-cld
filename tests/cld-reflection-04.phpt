--TEST--
ReflectionClass for CLD\Language and CLD\Encoding
--FILE--
<?php
$c1 = new ReflectionClass("CLD\Encoding");
$c2 = new ReflectionClass("CLD\Language");
var_dump($c1->getName(), $c1->isFinal(), $c1->getMethods(), $c1->getProperties());
var_dump($c2->getName(), $c2->isFinal(), $c2->getMethods(), $c2->getProperties());
?>
==DONE==
--EXPECT--
string(12) "CLD\Encoding"
bool(true)
array(0) {
}
array(0) {
}
string(12) "CLD\Language"
bool(true)
array(0) {
}
array(0) {
}
==DONE==
