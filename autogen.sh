#!/bin/sh
test -d m4 || mkdir -p m4
autoreconf -i
./configure $@
