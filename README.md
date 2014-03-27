# PHP Bindings for Chromium Compact Language Detector (CLD)
[![Build Status](https://secure.travis-ci.org/lstrojny/php-cld.svg)](http://travis-ci.org/lstrojny/php-cld)

This small extension provides bindings to use the Chromium Compact Language Detector
(http://code.google.com/p/chromium-compact-language-detector/) in PHP.


## Installation

 1. Checkout Chromium Language Detector from with `hg clone
    https://code.google.com/p/chromium-compact-language-detector`
 2. Run `./build.sh`
 3. Checkout this project
 4. Run `phpize && ./configure --with-libcld-dir=... && make && sudo make install`
 5. Add `extension=cld.so` to your `php.ini`

## Usage

### Procedural API
```php
<?php
var_export(CLD\detect("Drüben hinterm Dorfe wohnt ein Leiermann. Und mit starren Fingern spielt er was er kann"));
var_export(CLD\detect("日[の]本([の]国", false, true, null, CLD\Language::JAPANESE, CLD\Encoding::JAPANESE_EUC_JP));
```

### Object-oriented API

```php
<?php
$detector = new CLD\Detector();
var_export($detector->detectLanguage('Drüben hinterm Dorfe wohnt ein Leiermann. Und mit starren Fingern spielt er was er kann'));

$detector->setLanguageHint(CLD\Language::JAPANESE);
$detector->setEncodingHint(CLD\Encoding::JAPANESE_EUC_JP);
$detector->detectLanguage("日[の]本([の]国", false);
```

will return

```text
array (
  0 =>
  array (
    'name' => 'GERMAN',
    'code' => 'de',
    'reliable' => true,
    'bytes' => 90,
  ),
)
array (
  0 =>
  array (
    'name' => 'JAPANESE',
    'code' => 'ja',
    'reliable' => true,
    'bytes' => 22,
  ),
  1 =>
  array (
    'name' => 'CHINESE',
    'code' => 'zh',
    'reliable' => true,
    'bytes' => 22,
  ),
)
```
