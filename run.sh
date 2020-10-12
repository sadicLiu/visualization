rm -rf build

mkdir build && cd build
cp ../military.flv ./

cmake ..
make -j

./run pred
