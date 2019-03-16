#include "Description.hpp"

Description::Description(){
	texture = new Texture;
	texture->loadFromFile("Img/Description.png");
	
	setSize({ 1280,720 });
	setTexture(texture);

	soundB.loadFromFile("Sound/click.ogg");
	clickSound.setBuffer(soundB);
}

void Description::draw(RenderWindow& window) {
	window.draw(*this);
}

Description::Type Description::run(RenderWindow& window, bool sound) {
	
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };

		if (pos.x >= 490 && pos.x <= 790 && pos.y >= 610 && pos.y <= 685) {
			if (sound) clickSound.play();

			return Type::Return;
		}
	}
	return Type::None;
}

Description::~Description(){
	delete texture;
}