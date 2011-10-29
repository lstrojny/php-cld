--TEST--
CLD\Detector basic functionality
--FILE--
<?php
$detector = new CLD\Detector();
var_dump($detector->getIncludeExtendedLanguages());
var_dump($detector->setIncludeExtendedLanguages(true));
var_dump($detector->getIncludeExtendedLanguages());
var_dump($detector->setIncludeExtendedLanguages(false));
var_dump($detector->getIncludeExtendedLanguages());
var_dump($detector->setIncludeExtendedLanguages());
var_dump($detector->getIncludeExtendedLanguages(1, 2));
?>
==DONE==
--EXPECTF--
bool(false)
NULL
bool(true)
NULL
bool(false)

Warning: CLD\Detector::setIncludeExtendedLanguages() expects exactly 1 parameter, 0 given in %scld-detector-includeExtendedLanguages.php on line %d
NULL

Warning: CLD\Detector::getIncludeExtendedLanguages() expects exactly 0 parameters, 2 given in %scld-detector-includeExtendedLanguages.php on line %d
NULL
==DONE==
