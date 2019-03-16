#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include "Intro.hpp"
#include "Menu.hpp"
#include "Play.hpp"
#include "Editor.hpp"
#include "Options.hpp"
#include "Description.hpp"
#include "FPS.hpp"

using namespace sf;
using namespace std;

class Game{

	enum Type {
		InIntro,
		InMenu,
		InGame,
		InEditor,
		InDescription,
		InOptions,
	};

	Intro* intro;

	Menu* menu;

	//
	
	Play* play;

	Editor* editor;

	Description* description;

	Options* options;

	FPS* FpsCounter;

	//

	Type type;

	bool sound;

	bool fpsCounter;

	Clock clickDelay;

public:

	Game(RenderWindow& window);
	
	void run(RenderWindow& window);

	void draw(RenderWindow& window);

	~Game();
};

