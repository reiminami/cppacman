all:
	g++ src/main.cpp src/PacMan.cpp -o app -std=c++17 \
	-I/opt/homebrew/opt/sfml@2/include \
	-L/opt/homebrew/opt/sfml@2/lib \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-Wno-deprecated-declarations
