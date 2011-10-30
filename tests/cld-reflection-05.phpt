--TEST--
Reflection for CLD\Detector
--FILE--
<?php
var_dump(new CLD\Detector());
ReflectionClass::export("CLD\Detector");
?>
==DONE==
--EXPECTF--
object(CLD\Detector)#%d (4) {
  ["includeExtendedLanguages":protected]=>
  bool(true)
  ["topLevelDomainHint":protected]=>
  NULL
  ["languageHint":protected]=>
  NULL
  ["encodingHint":protected]=>
  int(-1)
}
Class [ <internal:cld> class CLD\Detector ] {

  - Constants [0] {
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [4] {
    Property [ <default> protected $includeExtendedLanguages ]
    Property [ <default> protected $topLevelDomainHint ]
    Property [ <default> protected $languageHint ]
    Property [ <default> protected $encodingHint ]
  }

  - Methods [9] {
    Method [ <internal:cld> public method setIncludeExtendedLanguages ] {

      - Parameters [1] {
        Parameter #0 [ <required> $includeExtendedLanguages ]
      }
    }

    Method [ <internal:cld> public method getIncludeExtendedLanguages ] {

      - Parameters [0] {
      }
    }

    Method [ <internal:cld> public method setTopLevelDomainHint ] {

      - Parameters [1] {
        Parameter #0 [ <required> $topLevelDomainHint ]
      }
    }

    Method [ <internal:cld> public method getTopLevelDomainHint ] {

      - Parameters [0] {
      }
    }

    Method [ <internal:cld> public method setLanguageHint ] {

      - Parameters [1] {
        Parameter #0 [ <required> $languageHint ]
      }
    }

    Method [ <internal:cld> public method getLanguageHint ] {

      - Parameters [0] {
      }
    }

    Method [ <internal:cld> public method setEncodingHint ] {

      - Parameters [1] {
        Parameter #0 [ <required> $encodingHint ]
      }
    }

    Method [ <internal:cld> public method getEncodingHint ] {

      - Parameters [0] {
      }
    }

    Method [ <internal:cld> public method detectLanguage ] {

      - Parameters [2] {
        Parameter #0 [ <required> $text ]
        Parameter #1 [ <optional> $isPlainText ]
      }
    }
  }
}

==DONE==
