# build all targets and start drogon web server
# use 'make test' in build directory to start tests

rm -rf build && mkdir build && cd build && cmake -D BUILD_TESTS=ON .. && make
cd ../build && ./increa_proj