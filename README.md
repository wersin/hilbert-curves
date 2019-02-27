# Hilbert Kurven Aufgabe A209

Creates .svg or .html file with the specified degree for a Curve



![hilbert 6th degree](img/hilbert_4.png)

## Getting Started

In the `./src/` folder you will find all the source code necesary for the program. Just need to compile the
Project first running: 
```
make
```

Afterwards the executable program is placed in the `./bin/` subfolder. Run it directly there
or using the `run.sh`

```
./run.sh -d7 -f foo -t
```
Taht command will generate `foo_7.html` in the `./output/` folder. To view it run:
```
firefox output/foo_7.html
```
### Prerequisites

If you want to run the tests you will also need `gnuplot`, and python 3.


## Running the tests

In the `./tests/` folder you will find `run-tests.py` and `run.sh`.

Executing `./run.sh` will run the C-Algorithm against the x86-Assembler Algorithm from
a `start_degree` to an `end_degree` and plot the average time needed for both algorithms
in .png or directly visualized by gnuplot.

In case `gnuplot` is not installed the python script will generate an output file with the
avg times for each algorithm.


## Author

* Mark Bley
