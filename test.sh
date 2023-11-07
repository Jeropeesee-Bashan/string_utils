#!/bin/sh

! command -v make >/dev/null && uninstalled="make ${uninstalled}"
! command -v git >/dev/null && uninstalled="git ${uninstalled}"

if [ -n "${uninstalled}" ]
then
    uninstalled=$(echo "${uninstalled}" | sed 's/ $//' | sed 's/ /, /')
    >&2 echo "Cannot find executables: ${uninstalled}."
    >&2 echo "Please, install these programs to do tests."
    exit 1
fi

cd ./test/

[ ! -d ./greatest/ ] && \
! git clone https://github.com/silentbicycle/greatest -o greatest && \
>&2 echo "Got an error from git. Maybe can't access the \"greatest\" repo." && \
exit 2

echo "Compiling tests..."
if ! make test >/dev/null
then
    echo >&2 "An error occured during compilation."
    make clean >/dev/null 2>&1
    exit 3
fi

./test
