#!/bin/bash
grep --color=auto -Pvn '(1|2) [0-9\.]+ (i|o)[a-z]* [0-9]{1,2} [0-9\.]+ (f|b)[a-z]* (fh|bh|fs|bs)' $@
