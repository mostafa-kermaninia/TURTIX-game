all: compile link run

compile:
	g++ -c main.cpp Game.cpp Menu.cpp Map.cpp Player.cpp Baby_turtle.cpp Enemy1.cpp Enemy2.cpp -I"C:\Users\mosta\Documents\libraries\SFML-2.5.1\include" -DSFML_STATIC 

link:
	g++ main.o Game.o Menu.o Map.o Player.o Baby_turtle.o Enemy1.o Enemy2.o -o Final -L"C:\Users\mosta\Documents\libraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-audio-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main 
	
run:
	./Final