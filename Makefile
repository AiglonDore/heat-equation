CC=g++

ifeq ($(RELEASE), TRUE)
CFLAGS=-Wall -Wextra -s -O3 -std=c++2a
else
CFLAGS=-Wall -Wextra -std=c++2a -g
endif

all : heat-equation.out

heat-equation.out : obj/main.o obj/exn.o obj/materials.o obj/bar.o obj/computation.o
	$(CC) $(CFLAGS) -o bin/$@ $^ `pkg-config --cflags --libs sdl2`

obj/main.o : src/main.cpp header/exn.h header/materials.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/exn.o : src/exn.cpp header/exn.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/materials.o : src/materials.cpp header/materials.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/bar.o : src/bar.cpp header/bar.h header/exn.h header/materials.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/computation.o : src/computation.cpp header/computation.h header/bar.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f obj/*.o bin/*.out

doc :
	doxygen Doxyfile