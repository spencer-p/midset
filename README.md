# Midset Calculator

This is a command line utility for calculating midsets. Marching bands and drum
corps march between coordinates on a field and knowing the midpoint between two
coordinates is beneficial to the accuracy of the performers. However,
coordinates on a football field are not normal cartesian coordinates, so these
calculations can be tricky. This calculator takes care of the hard work.

## Building it

```
git clone https://github.com/spencer-p/midset.git
cd midset
make
```

## Using it

### Input

The executable file will be named midset and will accept a file to read your
dots from. Alternatively, it will read standard input, allowing things like
piping data to it.

```
./midset mydots.txt
```

### Options

In addition, there are a couple of fancy options:
```
./midset [file]
	Accepts a file to read, otherwise stdin
	-u: ugly output
	-n: output set numbers
	-a: also print input sets
	-d [n]: division of sets (2, 4, 8...)
```

### Format for dots

`[side] [steps] [in/out] [yard] [steps] [front/back] [fh/bh/fs/bs]`
