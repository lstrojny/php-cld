--TEST--
void CLD\Detector::setLanguageHint(string language) / string CLD\Detector::getLanguageHint()
--FILE--
<?php
$detector = new CLD\Detector();
var_dump($detector->getLanguageHint());
var_dump($detector->setLanguageHint('en'));
var_dump($detector->getLanguageHint());
var_dump($detector->setLanguageHint(''));
var_dump($detector->getLanguageHint());
var_dump($detector->setLanguageHint('EN'));
var_dump($detector->getLanguageHint());
var_dump($detector->setLanguageHint(null));
var_dump($detector->getLanguageHint());
var_dump($detector->setLanguageHint());
var_dump($detector->getLanguageHint('param'));
?>
==DONE==
--EXPECTF--
NULL
NULL
string(2) "en"
NULL
NULL
NULL
string(2) "en"
NULL
NULL

Warning: CLD\Detector::setLanguageHint() expects exactly 1 parameter, 0 given in %scld-detector-languageHint.php on line %d
NULL

Warning: CLD\Detector::getLanguageHint() expects exactly 0 parameters, 1 given in %scld-detector-languageHint.php on line %d
NULL
==DONE==
