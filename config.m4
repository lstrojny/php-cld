PHP_ARG_ENABLE(cld, enable Chromium Compact Language Detector,
[  --enable-cld Enable Chromium Compact Language Detector])

if test -z "$PHP_LIBCLD_DIR"; then
  PHP_ARG_WITH(libcld-dir, libcld install dir,
  [  --with-libcld-dir=DIR    Chromium Compact Language Detector: libcld install prefix], no, no)
fi

if test "$PHP_CLD" != "no"; then
    if ! test -f $PHP_LIBCLD_DIR/internal/libcld2.so; then
        AC_MSG_ERROR([libcld not found. Specify installation directory with --with-libcld-dir=])
    fi

    PHP_REQUIRE_CXX()
    PHP_SUBST(CLD_SHARED_LIBADD)
    PHP_ADD_INCLUDE($PHP_LIBCLD_DIR)
    PHP_ADD_LIBRARY(stdc++, 1, CLD_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(cld2, $PHP_LIBCLD_DIR/internal, CLD_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(cld2_full, $PHP_LIBCLD_DIR/internal, CLD_SHARED_LIBADD)
    PHP_NEW_EXTENSION(cld, cld.cc, $ext_shared)

    CXXFLAGS="-Wall -Wno-write-strings"
fi
