--TEST--
ReflectionFunction for CLD\detect()
--FILE--
<?php
$r = new ReflectionFunction("CLD\detect");
var_dump($r->getName());
ReflectionFunction::export("CLD\detect");
foreach ($r->getParameters() as $param) {
	echo $param->getName() . "\n";
	var_dump($param->isOptional(), $param->allowsNull(), $param->isArray());
}
?>
==DONE==
--EXPECT--
string(10) "CLD\detect"
Function [ <internal:cld> function CLD\detect ] {

  - Parameters [6] {
    Parameter #0 [ <required> $text ]
    Parameter #1 [ <optional> $is_plain_text ]
    Parameter #2 [ <optional> $include_extended_languages ]
    Parameter #3 [ <optional> $top_level_domain_hint ]
    Parameter #4 [ <optional> $language_hint ]
    Parameter #5 [ <optional> $encoding_hint ]
  }
}

text
bool(false)
bool(false)
bool(false)
is_plain_text
bool(true)
bool(false)
bool(false)
include_extended_languages
bool(true)
bool(false)
bool(false)
top_level_domain_hint
bool(true)
bool(false)
bool(false)
language_hint
bool(true)
bool(false)
bool(false)
encoding_hint
bool(true)
bool(false)
bool(false)
==DONE==
