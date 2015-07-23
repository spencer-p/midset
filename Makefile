midset: midset.c dot.c dot.h
	cc midset.c dot.c -o midset -lm
distance: distance.c dot.c dot.h
	cc distance.c dot.c -o distance -lm
debug: midset.c dot.c dot.h
	cc midset.c dot.c -o midset -lm -g
