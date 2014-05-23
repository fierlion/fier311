#1/bin/bash

make
./primeMProc -m 10000 -c 10 > primeMTest.txt
diff twinPrimes.txt primeMTest.txt
make clean
