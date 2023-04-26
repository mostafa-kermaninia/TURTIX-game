all: player map game main final_result run

player: Player.h
	g++ -c --std=c++11 Player.cpp -o Player.o 
map: Map.h
	g++ -c --std=c++11 Map.cpp -o Map.o 
game: Game.h
	g++ -c --std=c++11 Game.cpp -o Game.o
main: Game.o Game.h Player.o Player.h Map.o Map.h
	g++ -c --std=c++11 main.cpp -o main.o
final_result: main.o Game.o Game.h Player.o Player.h Map.o Map.h
	g++ --std=c++11 Map.o Player.o main.o Game.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o main.out
run:
	./main.out