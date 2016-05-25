.all: VMtranslator

VMtranslator: obj/VMtranslator.o obj/parser.o 
	g++ -std=c++11 -Wall -pedantic -o VMtranslator obj/VMtranslator.o obj/parser.o
	
obj/VMtranslator.o: VMtranslator.cpp
	g++ -std=c++11 -Wall -pedantic -c VMtranslator.cpp -o obj/VMtranslator.o
	
obj/parser.o: parser.cpp
	g++ -std=c++11 -Wall -pedantic -c parser.cpp -o obj/parser.o
	
clean:
	rm obj/*o VMtranslator.exe