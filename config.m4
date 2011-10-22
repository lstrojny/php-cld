PHP_ARG_ENABLE(ccld, enable chromium compact language detector,
[  --enable-ccld Enable Chromium compact language detector])

if test "$PHP_CCLD" != "no"; then
    CLD_LIBDIR=../

    PHP_REQUIRE_CXX()
    PHP_SUBST(CCLD_SHARED_LIBADD)
    PHP_ADD_INCLUDE($CLD_LIBDIR)
    PHP_ADD_LIBRARY_WITH_PATH(cld, $CLD_LIBDIR, CCLD_SHARED_LIBADD)
    PHP_NEW_EXTENSION(ccld, php_ccld.cc, $ext_shared)
    CXXFLAGS="-static"
    LDDFLAGS="-static"
fi
