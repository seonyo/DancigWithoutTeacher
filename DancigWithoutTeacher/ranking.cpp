#include "all.h"

void ranking() {

	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	Texture background;

	background.loadFromFile("image/background.png");

	Sprite backgroundImg(background);

	// �̹��� ũ�⸦ â ũ�⿡ �°� ���� (���� ���)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
			}

		}
		window.draw(backgroundImg);

		window.display();
	}
}