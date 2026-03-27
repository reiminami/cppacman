all:
	g++ src/main.cpp src/Game.cpp -o app \
	-I/opt/homebrew/opt/sfml@2/include \
	-L/opt/homebrew/opt/sfml@2/lib \
	-lsfml-graphics -lsfml-window -lsfml-system \
	-Wno-deprecated-declarations
# 	g++ src/main.cpp src/Game.cpp src/Map.cpp src/HUD.cpp -o app -std=c++17 \
# 	-I/opt/homebrew/opt/sfml@2/include \
# 	-L/opt/homebrew/opt/sfml@2/lib \
# 	-lsfml-graphics -lsfml-window -lsfml-system \
# 	-Wno-deprecated-declarations
