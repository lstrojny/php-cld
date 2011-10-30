--TEST--
ReflectionClass for CLD\Language and CLD\Encoding
--FILE--
<?php
ReflectionClass::export("CLD\Encoding");
ReflectionClass::export("CLD\Language");
?>
==DONE==
--EXPECT--
Class [ <internal:cld> final class CLD\Encoding ] {

  - Constants [75] {
    Constant [ integer ISO_8859_1 ] { 0 }
    Constant [ integer ISO_8859_2 ] { 1 }
    Constant [ integer ISO_8859_3 ] { 2 }
    Constant [ integer ISO_8859_4 ] { 3 }
    Constant [ integer ISO_8859_5 ] { 4 }
    Constant [ integer ISO_8859_6 ] { 5 }
    Constant [ integer ISO_8859_7 ] { 6 }
    Constant [ integer ISO_8859_8 ] { 7 }
    Constant [ integer ISO_8859_9 ] { 8 }
    Constant [ integer ISO_8859_10 ] { 9 }
    Constant [ integer JAPANESE_EUC_JP ] { 10 }
    Constant [ integer JAPANESE_SHIFT_JIS ] { 11 }
    Constant [ integer JAPANESE_JIS ] { 12 }
    Constant [ integer CHINESE_BIG5 ] { 13 }
    Constant [ integer CHINESE_GB ] { 14 }
    Constant [ integer CHINESE_EUC_CN ] { 15 }
    Constant [ integer KOREAN_EUC_KR ] { 16 }
    Constant [ integer UNICODE ] { 17 }
    Constant [ integer CHINESE_EUC_DEC ] { 18 }
    Constant [ integer CHINESE_CNS ] { 19 }
    Constant [ integer CHINESE_BIG5_CP950 ] { 20 }
    Constant [ integer JAPANESE_CP932 ] { 21 }
    Constant [ integer UTF8 ] { 22 }
    Constant [ integer UNKNOWN_ENCODING ] { 23 }
    Constant [ integer ASCII_7BIT ] { 24 }
    Constant [ integer RUSSIAN_KOI8_R ] { 25 }
    Constant [ integer RUSSIAN_CP1251 ] { 26 }
    Constant [ integer MSFT_CP1252 ] { 27 }
    Constant [ integer RUSSIAN_KOI8_RU ] { 28 }
    Constant [ integer MSFT_CP1250 ] { 29 }
    Constant [ integer ISO_8859_15 ] { 30 }
    Constant [ integer MSFT_CP1254 ] { 31 }
    Constant [ integer MSFT_CP1257 ] { 32 }
    Constant [ integer ISO_8859_11 ] { 33 }
    Constant [ integer MSFT_CP874 ] { 34 }
    Constant [ integer MSFT_CP1256 ] { 35 }
    Constant [ integer MSFT_CP1255 ] { 36 }
    Constant [ integer ISO_8859_8_I ] { 37 }
    Constant [ integer HEBREW_VISUAL ] { 38 }
    Constant [ integer CZECH_CP852 ] { 39 }
    Constant [ integer CZECH_CSN_369103 ] { 40 }
    Constant [ integer MSFT_CP1253 ] { 41 }
    Constant [ integer RUSSIAN_CP866 ] { 42 }
    Constant [ integer ISO_8859_13 ] { 43 }
    Constant [ integer ISO_2022_KR ] { 44 }
    Constant [ integer GBK ] { 45 }
    Constant [ integer GB18030 ] { 46 }
    Constant [ integer BIG5_HKSCS ] { 47 }
    Constant [ integer ISO_2022_CN ] { 48 }
    Constant [ integer TSCII ] { 49 }
    Constant [ integer TAMIL_MONO ] { 50 }
    Constant [ integer TAMIL_BI ] { 51 }
    Constant [ integer JAGRAN ] { 52 }
    Constant [ integer MACINTOSH_ROMAN ] { 53 }
    Constant [ integer UTF7 ] { 54 }
    Constant [ integer BHASKAR ] { 55 }
    Constant [ integer HTCHANAKYA ] { 56 }
    Constant [ integer UTF16BE ] { 57 }
    Constant [ integer UTF16LE ] { 58 }
    Constant [ integer UTF32BE ] { 59 }
    Constant [ integer UTF32LE ] { 60 }
    Constant [ integer BINARYENC ] { 61 }
    Constant [ integer HZ_GB_2312 ] { 62 }
    Constant [ integer UTF8UTF8 ] { 63 }
    Constant [ integer TAM_ELANGO ] { 64 }
    Constant [ integer TAM_LTTMBARANI ] { 65 }
    Constant [ integer TAM_SHREE ] { 66 }
    Constant [ integer TAM_TBOOMIS ] { 67 }
    Constant [ integer TAM_TMNEWS ] { 68 }
    Constant [ integer TAM_WEBTAMIL ] { 69 }
    Constant [ integer KDDI_SHIFT_JIS ] { 70 }
    Constant [ integer DOCOMO_SHIFT_JIS ] { 71 }
    Constant [ integer SOFTBANK_SHIFT_JIS ] { 72 }
    Constant [ integer KDDI_ISO_2022_JP ] { 73 }
    Constant [ integer SOFTBANK_ISO_2022_JP ] { 74 }
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [0] {
  }

  - Methods [0] {
  }
}

Class [ <internal:cld> final class CLD\Language ] {

  - Constants [161] {
    Constant [ string ENGLISH ] { en }
    Constant [ string DANISH ] { da }
    Constant [ string DUTCH ] { nl }
    Constant [ string FINNISH ] { fi }
    Constant [ string FRENCH ] { fr }
    Constant [ string GERMAN ] { de }
    Constant [ string HEBREW ] { he }
    Constant [ string ITALIAN ] { it }
    Constant [ string JAPANESE ] { ja }
    Constant [ string KOREAN ] { ko }
    Constant [ string NORWEGIAN ] { nb }
    Constant [ string POLISH ] { pl }
    Constant [ string PORTUGUESE ] { pt }
    Constant [ string RUSSIAN ] { ru }
    Constant [ string SPANISH ] { es }
    Constant [ string SWEDISH ] { sv }
    Constant [ string CHINESE ] { zh }
    Constant [ string CZECH ] { cs }
    Constant [ string GREEK ] { el }
    Constant [ string ICELANDIC ] { is }
    Constant [ string LATVIAN ] { lv }
    Constant [ string LITHUANIAN ] { lt }
    Constant [ string ROMANIAN ] { ro }
    Constant [ string HUNGARIAN ] { hu }
    Constant [ string ESTONIAN ] { et }
    Constant [ string TG_UNKNOWN_LANGUAGE ] { ut }
    Constant [ string UNKNOWN ] { un }
    Constant [ string BULGARIAN ] { bg }
    Constant [ string CROATIAN ] { hr }
    Constant [ string SERBIAN ] { sr }
    Constant [ string IRISH ] { ga }
    Constant [ string GALICIAN ] { gl }
    Constant [ string TAGALOG ] { fil }
    Constant [ string TURKISH ] { tr }
    Constant [ string UKRAINIAN ] { uk }
    Constant [ string HINDI ] { hi }
    Constant [ string MACEDONIAN ] { mk }
    Constant [ string BENGALI ] { bn }
    Constant [ string INDONESIAN ] { id }
    Constant [ string LATIN ] { la }
    Constant [ string MALAY ] { ms }
    Constant [ string MALAYALAM ] { ml }
    Constant [ string WELSH ] { cy }
    Constant [ string NEPALI ] { ne }
    Constant [ string TELUGU ] { te }
    Constant [ string ALBANIAN ] { sq }
    Constant [ string TAMIL ] { ta }
    Constant [ string BELARUSIAN ] { be }
    Constant [ string JAVANESE ] { jw }
    Constant [ string OCCITAN ] { oc }
    Constant [ string URDU ] { ur }
    Constant [ string BIHARI ] { bh }
    Constant [ string GUJARATI ] { gu }
    Constant [ string THAI ] { th }
    Constant [ string ARABIC ] { ar }
    Constant [ string CATALAN ] { ca }
    Constant [ string ESPERANTO ] { eo }
    Constant [ string BASQUE ] { eu }
    Constant [ string INTERLINGUA ] { ia }
    Constant [ string KANNADA ] { kn }
    Constant [ string PUNJABI ] { pa }
    Constant [ string SCOTS_GAELIC ] { gd }
    Constant [ string SWAHILI ] { sw }
    Constant [ string SLOVENIAN ] { sl }
    Constant [ string MARATHI ] { mr }
    Constant [ string MALTESE ] { mt }
    Constant [ string VIETNAMESE ] { vi }
    Constant [ string FRISIAN ] { fy }
    Constant [ string SLOVAK ] { sk }
    Constant [ string CHINESET ] { zh-TW }
    Constant [ string FAROESE ] { fo }
    Constant [ string SUNDANESE ] { su }
    Constant [ string UZBEK ] { uz }
    Constant [ string AMHARIC ] { am }
    Constant [ string AZERBAIJANI ] { az }
    Constant [ string GEORGIAN ] { ka }
    Constant [ string TIGRINYA ] { ti }
    Constant [ string PERSIAN ] { fa }
    Constant [ string BOSNIAN ] { bs }
    Constant [ string SINHALESE ] { si }
    Constant [ string NORWEGIAN_N ] { nn }
    Constant [ string PORTUGUESE_P ] { pt-PT }
    Constant [ string PORTUGUESE_B ] { pt-BR }
    Constant [ string XHOSA ] { xh }
    Constant [ string ZULU ] { zu }
    Constant [ string GUARANI ] { gn }
    Constant [ string SESOTHO ] { st }
    Constant [ string TURKMEN ] { tk }
    Constant [ string KYRGYZ ] { ky }
    Constant [ string BRETON ] { br }
    Constant [ string TWI ] { tw }
    Constant [ string YIDDISH ] { yi }
    Constant [ string SERBO_CROATIAN ] { sh }
    Constant [ string SOMALI ] { so }
    Constant [ string UIGHUR ] { ug }
    Constant [ string KURDISH ] { ku }
    Constant [ string MONGOLIAN ] { mn }
    Constant [ string ARMENIAN ] { hy }
    Constant [ string LAOTHIAN ] { lo }
    Constant [ string SINDHI ] { sd }
    Constant [ string RHAETO_ROMANCE ] { rm }
    Constant [ string AFRIKAANS ] { af }
    Constant [ string LUXEMBOURGISH ] { lb }
    Constant [ string BURMESE ] { my }
    Constant [ string KHMER ] { km }
    Constant [ string TIBETAN ] { bo }
    Constant [ string DHIVEHI ] { dv }
    Constant [ string CHEROKEE ] { chr }
    Constant [ string SYRIAC ] { syr }
    Constant [ string LIMBU ] { sit-NP }
    Constant [ string ORIYA ] { or }
    Constant [ string ASSAMESE ] { as }
    Constant [ string CORSICAN ] { co }
    Constant [ string INTERLINGUE ] { ie }
    Constant [ string KAZAKH ] { kk }
    Constant [ string LINGALA ] { ln }
    Constant [ string MOLDAVIAN ] { mo }
    Constant [ string PASHTO ] { ps }
    Constant [ string QUECHUA ] { qu }
    Constant [ string SHONA ] { sn }
    Constant [ string TAJIK ] { tg }
    Constant [ string TATAR ] { tt }
    Constant [ string TONGA ] { to }
    Constant [ string YORUBA ] { yo }
    Constant [ string CREOLES_AND_PIDGINS_ENGLISH_BASED ] { cpe }
    Constant [ string CREOLES_AND_PIDGINS_FRENCH_BASED ] { cpf }
    Constant [ string CREOLES_AND_PIDGINS_PORTUGUESE_BASED ] { cpp }
    Constant [ string CREOLES_AND_PIDGINS_OTHER ] { crp }
    Constant [ string MAORI ] { mi }
    Constant [ string WOLOF ] { wo }
    Constant [ string ABKHAZIAN ] { ab }
    Constant [ string AFAR ] { aa }
    Constant [ string AYMARA ] { ay }
    Constant [ string BASHKIR ] { ba }
    Constant [ string BISLAMA ] { bi }
    Constant [ string DZONGKHA ] { dz }
    Constant [ string FIJIAN ] { fj }
    Constant [ string GREENLANDIC ] { kl }
    Constant [ string HAUSA ] { ha }
    Constant [ string HAITIAN_CREOLE ] { ht }
    Constant [ string INUPIAK ] { ik }
    Constant [ string INUKTITUT ] { iu }
    Constant [ string KASHMIRI ] { ks }
    Constant [ string KINYARWANDA ] { rw }
    Constant [ string MALAGASY ] { mg }
    Constant [ string NAURU ] { na }
    Constant [ string OROMO ] { om }
    Constant [ string RUNDI ] { rn }
    Constant [ string SAMOAN ] { sm }
    Constant [ string SANGO ] { sg }
    Constant [ string SANSKRIT ] { sa }
    Constant [ string SISWANT ] { ss }
    Constant [ string TSONGA ] { ts }
    Constant [ string TSWANA ] { tn }
    Constant [ string VOLAPUK ] { vo }
    Constant [ string ZHUANG ] { za }
    Constant [ string KHASI ] { kha }
    Constant [ string SCOTS ] { sco }
    Constant [ string GANDA ] { lg }
    Constant [ string MANX ] { gv }
    Constant [ string MONTENEGRIN ] { sr-ME }
  }

  - Static properties [0] {
  }

  - Static methods [0] {
  }

  - Properties [0] {
  }

  - Methods [0] {
  }
}

==DONE==
