--TEST--
ReflectionExtension::getFunctions() for CLD\detect()
--FILE--
<?php
$re = new ReflectionExtension('cld');
$fn = $re->getFunctions();
var_dump(array_map(function($f) {return $f->getName();}, $fn));
?>
==DONE==
--EXPECT--
array(1) {
  ["CLD\detect"]=>
  string(10) "CLD\detect"
}
==DONE==
--SKIPIF--
<?php
if (version_compare(PHP_VERSION, '5.4') === -1) {
	die('Not supported');
}
