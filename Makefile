midset: midset.c dot.c dot.h
	cc midset.c dot.c -o midset -lm
debug: midset.c dot.c dot.h
	cc midset.c dot.c -o midset -lm -g
c99: midset.c dot.c dot.h
	cc midset.c dot.c -o midset -lm -std=c99
