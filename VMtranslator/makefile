.all: WMtranslator

WMtranslator: obj/WMtranslator.o obj/parser.o 
	g++ -std=c++11 -Wall -pedantic -o WMtranslator obj/WMtranslator.o obj/parser.o
	
obj/WMtranslator.o: WMtranslator.cpp
	g++ -std=c++11 -Wall -pedantic -c WMtranslator.cpp -o obj/WMtranslator.o
	
obj/parser.o: parser.cpp
	g++ -std=c++11 -Wall -pedantic -c parser.cpp -o obj/parser.o
	
clean:
	rm obj/*o WMtranslator.exe