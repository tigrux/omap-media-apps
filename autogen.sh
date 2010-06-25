#!/bin/sh
autoreconf -i

test -n "$NOCONFIGURE" && {
  echo "skipping configure stage as requested."
  echo "autogen.sh done."
  exit 0
}

./configure $@
