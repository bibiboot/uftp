#!/bin/bash

# Create 1Gb file
dd if=/dev/urandom of=etc/data/data.bin bs=1M count=1000

