# PHP Bindings for Chromium Compact Language Detector (CLD)

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
```php
<?php
var_export(CLD\detect("Ein bisschen deutschprachiger Text"));
var_export(CLD\detect("日[の]本([の]国", false, true, null, CLD\Language::JAPANESE, CLD\Encoding::JAPANESE_EUC_JP));
```

will return

```text
array (
  0 =>
  array (
    'name' => 'GERMAN',
    'code' => 'de',
    'reliable' => true,
    'bytes' => 37,
  ),
)
array (
  0 =>
  array (
    'name' => 'Japanese',
    'code' => 'ja',
    'reliable' => true,
    'bytes' => 22,
  ),
  1 =>
  array (
    'name' => 'Chinese',
    'code' => 'zh',
    'reliable' => true,
    'bytes' => 22,
  ),
)
```
