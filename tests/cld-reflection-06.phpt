--TEST--
Exception reflection
--FILE--
<?php
ReflectionClass::export('CLD\InvalidArgumentException');
ReflectionClass::export('CLD\InvalidLanguageException');
ReflectionClass::export('CLD\InvalidEncodingException');
?>
==DONE==
--EXPECT--
Class [ <internal:cld> abstract class CLD\InvalidArgumentException extends InvalidArgumentException ] {

  - Constants [0] {
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [4] {
    Property [ <default> protected $message ]
    Property [ <default> protected $code ]
    Property [ <default> protected $file ]
    Property [ <default> protected $line ]
  }

  - Methods [9] {
    Method [ <internal:Core, inherits Exception, ctor> public method __construct ] {

      - Parameters [3] {
        Parameter #0 [ <optional> $message ]
        Parameter #1 [ <optional> $code ]
        Parameter #2 [ <optional> $previous ]
      }
    }

    Method [ <internal:Core, inherits Exception> final public method getMessage ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getCode ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getFile ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getLine ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTrace ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getPrevious ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTraceAsString ] {
    }

    Method [ <internal:Core, inherits Exception> public method __toString ] {
    }
  }
}

Class [ <internal:cld> class CLD\InvalidLanguageException extends CLD\InvalidArgumentException ] {

  - Constants [0] {
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [4] {
    Property [ <default> protected $message ]
    Property [ <default> protected $code ]
    Property [ <default> protected $file ]
    Property [ <default> protected $line ]
  }

  - Methods [9] {
    Method [ <internal:Core, inherits Exception, ctor> public method __construct ] {

      - Parameters [3] {
        Parameter #0 [ <optional> $message ]
        Parameter #1 [ <optional> $code ]
        Parameter #2 [ <optional> $previous ]
      }
    }

    Method [ <internal:Core, inherits Exception> final public method getMessage ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getCode ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getFile ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getLine ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTrace ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getPrevious ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTraceAsString ] {
    }

    Method [ <internal:Core, inherits Exception> public method __toString ] {
    }
  }
}

Class [ <internal:cld> class CLD\InvalidEncodingException extends CLD\InvalidArgumentException ] {

  - Constants [0] {
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [4] {
    Property [ <default> protected $message ]
    Property [ <default> protected $code ]
    Property [ <default> protected $file ]
    Property [ <default> protected $line ]
  }

  - Methods [9] {
    Method [ <internal:Core, inherits Exception, ctor> public method __construct ] {

      - Parameters [3] {
        Parameter #0 [ <optional> $message ]
        Parameter #1 [ <optional> $code ]
        Parameter #2 [ <optional> $previous ]
      }
    }

    Method [ <internal:Core, inherits Exception> final public method getMessage ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getCode ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getFile ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getLine ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTrace ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getPrevious ] {
    }

    Method [ <internal:Core, inherits Exception> final public method getTraceAsString ] {
    }

    Method [ <internal:Core, inherits Exception> public method __toString ] {
    }
  }
}

==DONE==
