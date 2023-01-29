#!/bin/sh

cd ./test/
if [ ! -d "./greatest/" ]
then
    if ! command -v git &>/dev/null
    then
        >&2 echo "Git isn't installed."
        >&2 echo "Please install git to obtain the testing library."
        exit 1
    fi
    git clone https://github.com/silentbicycle/greatest -o greatest
    if [ "$?" -ne "0" ]
    then
        >&2 echo "Got an error from Git. Maybe can't access the \"greatest\" repo."
        exit 2
    fi
fi
if ! command -v make &>/dev/null
then
    >&2 echo "Make isn't installed."
    >&2 echo "Please install make to compile tests."
    exit 3
fi
echo "Compiling tests..."
make test >/dev/null
if [ "$?" -ne "0" ]
then
    >&2 echo "An error occured during compilation."
    make clean &>/dev/null
    exit 4
fi
./test
