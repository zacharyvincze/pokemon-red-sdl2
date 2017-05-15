build:
	g++ -o gen/pokemon src/*.cpp -framework SDL2 -framework SDL2_image
run:
	bin/pokemon
