#!/bin/bash

# prepara_ficheros.sh

if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

dir=$1

if [ -d "$dir" ]; then
    echo "Cleaning existing directory $dir..."
    rm -rf "$dir"/*
else
    echo "Creating directory $dir..."
    mkdir "$dir"
fi

cd "$dir" || exit 1

mkdir subdir
touch fichero1
echo "abcdefghij" > fichero2
ln -s fichero2 enlaceS
ln fichero2 enlaceH

echo
echo "File attributes using stat:"
for f in *; do
    echo "---- $f ----"
    stat "$f"
    echo
done
