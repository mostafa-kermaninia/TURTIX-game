all: enemy2 enemy1 player map game main final_result run

enemy2: Enemy2.h
	g++ -c --std=c++11 Enemy2.cpp -o Enemy2.o
enemy1: Enemy1.h
	g++ -c --std=c++11 Enemy1.cpp -o Enemy1.o 
player: Player.h
	g++ -c --std=c++11 Player.cpp -o Player.o 
map: Map.h Enemy1.o Enemy1.h Enemy2.o Enemy2.h
	g++ -c --std=c++11 Map.cpp -o Map.o 
game: Game.h Map.o Map.h Enemy1.o Enemy1.h Enemy2.o Enemy2.h
	g++ -c --std=c++11 Game.cpp -o Game.o
main: Game.o Game.h Player.o Player.h Map.o Map.h
	g++ -c --std=c++11 main.cpp -o main.o
final_result: main.o Game.o Game.h Player.o Player.h Map.o Map.h Enemy1.h Enemy1.o Enemy2.o Enemy2.h
	g++ --std=c++11 Map.o Player.o main.o Game.o Enemy1.o Enemy2.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o main.out
run:
	./main.out