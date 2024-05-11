
all:  compile link

compile: 
	g++ -c main.cpp -I "D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\include"
	

link: 
	g++ main.o -o ice -L "D:\SFML\64\SFML-2.6.1-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system