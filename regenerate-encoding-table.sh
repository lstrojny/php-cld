#!/bin/bash
echo -en "#include \"public/encodings.h\"\nusing namespace CLD2;\nstruct cld_encoding {\n\tconst char *name;\n\tEncoding encoding;\n};\nstatic const cld_encoding cld_encoding_info[] = {\n";
grep " = " $1/public/encodings.h | grep -v NUM_ENCODINGS |  awk -F " " '{print "{\""$1"\", "$1"},"}'
echo -en "};"
