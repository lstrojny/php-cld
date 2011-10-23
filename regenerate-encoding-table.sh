#!/bin/bash
echo -en "#include \"encodings/proto/encodings.pb.h\"\nstruct cld_encoding {\n\tconst char *name;\n\tEncoding encoding;\n};\nstatic const cld_encoding cld_encoding_info[] = {\n";
grep " = " ../encodings/proto/encodings.pb.h | grep -v NUM_ENCODINGS |  awk -F " " '{print "{\""$1"\", "$1"},"}'
echo -en "};"
