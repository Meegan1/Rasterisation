a.out: main.o Render.o Image.o Texture.o
	g++ -std=c++11 main.o Render.o Image.o Texture.o

main.o: main.cpp Image.h Render.h Texture.h Triangle.h Vertex.h
	g++ -std=c++11 -c main.cpp

Render.o: Render.cpp Render.h
	g++ -std=c++11 -c Render.cpp

Texture.o: Texture.cpp Texture.h
	g++ -std=c++11 -c Texture.cpp

Image.o: Image.cpp Image.h
	g++ -std=c++11 -c Image.cpp