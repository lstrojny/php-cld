--TEST--
void CLD\Detector::setTopLevelDomainHint(string tld) / string CLD\Detector::getTopLevelDomainHint()
--FILE--
<?php
$detector = new CLD\Detector();
var_dump($detector->getTopLevelDomainHint());
var_dump($detector->setTopLevelDomainHint('com'));
var_dump($detector->getTopLevelDomainHint());
var_dump($detector->setTopLevelDomainHint(''));
var_dump($detector->getTopLevelDomainHint());
var_dump($detector->setTopLevelDomainHint(null));
var_dump($detector->getTopLevelDomainHint());
var_dump($detector->setTopLevelDomainHint());
var_dump($detector->getTopLevelDomainHint('param'));
?>
==DONE==
--EXPECTF--
NULL
NULL
string(3) "com"
NULL
NULL
NULL
NULL

Warning: CLD\Detector::setTopLevelDomainHint() expects exactly 1 parameter, 0 given in %scld-detector-topLevelDomainHint.php on line %d
NULL

Warning: CLD\Detector::getTopLevelDomainHint() expects exactly 0 parameters, 1 given in %scld-detector-topLevelDomainHint.php on line %d
NULL
==DONE==
