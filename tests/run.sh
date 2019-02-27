#!/bin/sh

python run-tests.py
command -v gnuplot >/dev/null 2>&1 || {
    echo >&2 "Gnuplot it's not installed.";
    echo >&2 "Not generating a png.";
    exit 1;
}
gnuplot -p plot-config
echo "Graph was generatedin result-plot.png"
