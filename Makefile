CXX =		g++

CXXFLAGS +=	-I./lib/LibBomberman_linux_x64/includes/ -I./src/Game/ -I./src/Draw/ -I./src/Box/ -I./src/Player/ -I./src/Bonus/ -I./src/Bomb/ -I./src/Menu/ -I./src/Load/ -I./src/ -W -Wall -std=c++11 -I./lib/fmod/

LDFLAGS +=	-L./lib/LibBomberman_linux_x64/libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lSDL2_ttf -lSDL2_image ./lib/fmod/lib/libfmodexL64.so

NAME =		bomberman

SRC =		src/main.cpp			\
		src/Sound.cpp			\
		src/Menu/Menu.cpp		\
		src/Menu/MSetting.cpp		\
		src/Menu/MapGenerator.cpp	\
		src/Menu/Generator.cpp		\
		src/Menu/MParsing.cpp		\
		src/Draw/Cube.cpp		\
		src/Draw/Plan.cpp		\
		src/Bonus/Addbomb.cpp		\
		src/Bonus/Addspeed.cpp		\
		src/Bonus/Addrange.cpp		\
		src/Bonus/Addlife.cpp		\
		src/Bomb/Bomb.cpp		\
		src/Box/Box.cpp			\
		src/Box/Wall.cpp		\
		src/Box/Empty.cpp		\
		src/Game/Ressource.cpp		\
		src/Game/Pause.cpp		\
		src/Game/MyGame.cpp		\
		src/Game/Camera.cpp		\
		src/Game/Pars.cpp		\
		src/Player/HUD.cpp		\
		src/Player/Player.cpp		\
		src/Load/Load.cpp

OBJ =		$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ) *~ *#

fclean: clean
	rm -f $(NAME)

re: fclean all
