# Install dependencies

sudo apt update

sudo apt install g++ libsdl2-dev make

if [ -z -f Makefile ]; then
    echo "Makefile not found"
    exit 1
fi
if [ -z -d bin ]; then
    mkdir bin
fi
if [ -z -d obj ]; then
    mkdir obj
fi

# Build the appliation
sudo make install

# Clean the mess
make clean