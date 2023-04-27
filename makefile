all: compile link run

compile:
	g++ -c main.cpp Game.cpp Map.cpp Player.cpp  -I"C:\Users\mosta\Documents\libraries\SFML-2.5.1\include" -DSFML_STATIC 
	 
link:
	g++ main.o Game.o Map.o Player.o  -o Final -L"C:\Users\mosta\Documents\libraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main 

run:
	./Final