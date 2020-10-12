rm -r -fo cmake-build-debug

mkdir cmake-build-debug
cd cmake-build-debug
cp ../military.flv ./
cp ../tank.jpg ./

cmake -G"Unix Makefiles" ..
make -j

cd ..

./cmake-build-debug/run demo

