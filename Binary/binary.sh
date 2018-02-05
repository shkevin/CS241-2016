#!/bin/bash
./binary -d -8 12
./binary -d -8 127
./binary -d -8 128
./binary -d -8 255
./binary -d -8 300
./binary -d -16 300
./binary -d -32 300
./binary -d -16 32767
./binary -d -16 32768
./binary -d -64 300
./binary -b -8 101010
./binary -b -8 111100001
./binary -b -16 111100001
./binary -b -16 111100001111
./binary -b -16 1111000011110000
./binary -b -32 1111000011110011
./binary -b -32 111100001111000011110000
./binary -b -32 11111111111111111111111111111111
./binary -e -8 101
./binary -b -9 101
./binary -b -8 121
./binary -d -8 1a1
./binary -d -8
