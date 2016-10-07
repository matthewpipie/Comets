.PHONY: all clean
all:
	 g++ `sdl2-config --libs --cflags` *.cpp -o Comets -std=c++11 -fpermissive -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
clean:
	rm -f Comets
