#!/bin/sh
# Transfer a satisfactory build: bin/BIOS.lib -> lib/, src/BIOS/*.h -> include/BIOS/
set -e
cd "$(dirname "$0")"

LIB=bin/BIOS.lib

if [ ! -f "$LIB" ]; then
    echo "transfer: $LIB not found - build first (./cmk.sh && ./bld.sh in src)" >&2
    exit 1
fi

mkdir -p lib include/BIOS

cp "$LIB" lib/

# clear old headers so ones deleted from src/BIOS don't linger
rm -f include/BIOS/*.h
cp src/BIOS/*.h include/BIOS/

echo "transfered: lib/BIOS.lib + $(ls include/BIOS/*.h | wc -l | tr -d ' ') headers -> include/BIOS/"
