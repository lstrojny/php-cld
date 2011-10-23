--TEST--
ReflectionExtension::getFunctions() for CLD\detect()
--FILE--
<?php
$re = new ReflectionExtension('cld');
$fn = $re->getFunctions();
var_dump(array_map(function($f) {return $f->getName();}, $fn));
?>
==DONE==
--XFAIL--
Namespaced functions cause ReflectionExtension to fail in PHP 5.3
--EXPECT--
array(1) {
  [0]=>
    string(12) "CLD\detect()"
}
==DONE==
