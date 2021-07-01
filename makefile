all: engClasses.cpp

ec: engClasses.cpp
	g++ engClasses.cpp -o ec -lsfml-graphics -lsfml-window -lsfml-system