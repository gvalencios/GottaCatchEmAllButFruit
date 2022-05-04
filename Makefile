#Makefile

FLAGS = -pedantic-errors -std=c++11

play.o: play.cpp play.h
	g++ $(FLAGS) -c $<

main.o: main.cpp play.h
	g++ $(FLAGS) -c $<

play: main.o play.o
	g++ $(FLAGS) $^ -o $@

run: play
	./play

clean:
	rm -f play play.o main.o

.PHONY: clean
