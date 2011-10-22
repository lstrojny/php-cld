# PHP Bindings for Chromium Compact Language Detector (CCLD)

This small extension provides bindings to use the Chromium Compact Language Detector
(http://code.google.com/p/chromium-compact-language-detector/) in PHP.


## Installation

 1. Checkout Chromium Language Detector from with `hg clone
    https://code.google.com/p/chromium-compact-language-detector`
 2. Run `./build.sh`
 3. Checkout this project
 4. Edit `config.m4` and set the variable `CCLD_LIBDIR` to the directory where CCLD is located
 5. Run `phpize && ./configure && make && sudo make install`
 6. Add `extension=ccld.so` to your `php.ini`

## Usage
```php
<?php
var_export(CCLD\detect("Ein bisschen deutschprachiger Text"));
```

will return

```text
array (
  0 =>
  array (
    'name' => 'ENGLISH',
    'code' => 'en',
    'reliable' => true,
    'bytes' => 93,
  ),
)
```
