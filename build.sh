if ! [[ -d "build" ]]; then
    mkdir build;
fi
cd build

if [[ "$OSTYPE" == "linux-gnu"* ]] || [[ "$OSTYPE" == "darwin"* ]]; then
    generator="Unix Makefiles";
elif [[ "$OSTYPE" == "msys" ]]; then
    generator="MinGW Makefiles";
else
    exit -1;
fi

cmake .. -G"$generator"
cmake --build .
