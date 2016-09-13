.PHONY: all clean
all:
	 g++ `sdl2-config --libs --cflags` -lSDL2_image -fpermissive CollisionCalculator.cpp Comet.cpp Comets.cpp Constants.cpp Errors.cpp MainGame.cpp Player.cpp Sprite.cpp Star.cpp -o Comets
clean:
	rm -f Comets
