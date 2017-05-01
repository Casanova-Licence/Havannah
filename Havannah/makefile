make : mrproper Havanah.exe

Havanah.exe : ./object/main.o ./object/Game.o ./object/Player.o ./object/Plateau.o
	g++ -std=c++11 -pedantic -o $@ $^

./object/main.o : main.cpp
	g++ -std=c++11 -pedantic -o $@ -c $^

./object/Game.o : ./src/Game.cpp ./include/Game.h
	g++ -std=c++11 -pedantic -o $@ -c ./src/Game.cpp

./object/Plateau.o : ./src/Plateau.cpp ./include/Plateau.h
	g++ -std=c++11 -pedantic -o $@ -c ./src/Plateau.cpp

./object/Player.o : ./src/Player.cpp ./include/Player.h
	g++ -std=c++11 -pedantic -o $@ -c ./src/Player.cpp

clean:
	rm -f ./object/*.o
	rm -f *~

mrproper: clean
	rm -f Havanah.exe