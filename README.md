# PHP bindings for Chromium Language Detector

This small extension provides bindings to use the Chromium Language Detector
(http://code.google.com/p/chromium-compact-language-detector/) in PHP.


## Installation

 1. Checkout Chromium Language Detector from with `hg clone
    https://code.google.com/p/chromium-compact-language-detector
 2. Run `./build.sh`
 3. Checkout this project
 4. Run `phpize && ./configure && make && sudo make install`
 5. Add `extension=ccld.so` to your `php.ini`

## Usage
```php
var_dump(CCLD\detect("Ein bisschen deutschprachiger Text"));
```

will return

```text
array(1) {
  [0]=>
  array(4) {
    ["name"]=>
    string(6) "GERMAN"
    ["code"]=>
    string(2) "de"
    ["reliable"]=>
    bool(true)
    ["bytes"]=>
    int(37)
  }
}
```
