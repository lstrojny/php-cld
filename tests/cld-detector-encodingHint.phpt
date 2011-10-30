--TEST--
void CLD\Detector::setEncodingHint(int encodingHint) / int CLD\Detector::getEncodingHint()
--FILE--
<?php
$detector = new CLD\Detector();
var_dump($detector->getEncodingHint());
var_dump($detector->setEncodingHint(CLD\Encoding::UTF8UTF8));
var_dump($detector->getEncodingHint());
var_dump($detector->setEncodingHint(-1));
var_dump($detector->getEncodingHint());
var_dump($detector->getEncodingHint("arg"));
var_dump($detector->setEncodingHint());
try {
	$detector->setEncodingHint("1000000000");
} catch (CLD\InvalidArgumentException $e) {
	var_dump(get_class($e), $e->getMessage(), $e->getCode());
}
?>
==DONE==
--EXPECTF--
int(-1)
NULL
int(63)
NULL
int(-1)

Warning: CLD\Detector::getEncodingHint() expects exactly 0 parameters, 1 given in %scld-detector-encodingHint.php on line %d
NULL

Warning: CLD\Detector::setEncodingHint() expects exactly 1 parameter, 0 given in %scld-detector-encodingHint.php on line %d
NULL
string(%d) "CLD\InvalidEncodingException"
string(%d) "Invalid encoding "1000000000""
int(100)
==DONE==
