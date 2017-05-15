build:
	g++ -o bin/pokemon src/*.cpp -framework SDL2 -framework SDL2_image
run:
	bin/pokemon
