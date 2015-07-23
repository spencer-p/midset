# Midset Calculator

This is a command line utility for calculating midsets.

## Building it

```
git clone https://github.com/springworm/midset.git
cd midset
make
```

If you want to "install" it figure it out yourself.

## How to use

### Input

The executable file will be named midset and will accept a file to read your dots from. Alternatively, it will read standard input, allowing things like piping data to it.

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
