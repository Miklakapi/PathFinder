#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace sf;
using namespace std;

class Description : public RectangleShape{

public:

	enum Type {
		None,
		Return
	};

private:

	Texture* texture;

	SoundBuffer soundB;

	Sound clickSound;

public:

	Description();

	void draw(RenderWindow& window);

	Type run(RenderWindow& window, bool sound);

	~Description();
};

