all: prog

prog: assembler.o parser.o
	g++ -Wall -o assembler obj/assembler.o obj/parser.o
	
assembler.o: assembler.cpp
	g++ -Wall -c assembler.cpp -o obj/assembler.o
	
parser.o: parser.cpp
	g++ -Wall -c parser.cpp -o obj/parser.o
	
clean:
	rm obj/*o assembler.exe