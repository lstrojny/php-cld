--TEST--
ReflectionExtension::getName() for CLD\detect()
--FILE--
<?php
$re = new ReflectionExtension('cld');
var_dump($re->getName());
--EXPECT--
string(3) "cld"
