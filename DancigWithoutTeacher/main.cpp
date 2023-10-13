#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode(1500, 1000), "������ ���� ���߱�");

	Texture background;
	Texture mainContent;

	background.loadFromFile("image/background.png");
	mainContent.loadFromFile("image/mainContent.png");

	Sprite backgroundImg(background);
	Sprite mainContentImg(mainContent);


	// �̹��� ũ�⸦ â ũ�⿡ �°� ���� (���� ���)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);
	mainContentImg.setScale(
		500.0f / mainContent.getSize().x,
		220.0f / mainContent.getSize().y
	);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
		window.draw(mainContentImg);
	
		window.display();
	}
}
