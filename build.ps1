rm -r -fo cmake-build-debug
rm run.exe

mkdir cmake-build-debug
cd cmake-build-debug

cmake -G"Unix Makefiles" ..
make -j
cp ./run.exe ..

cd ..
