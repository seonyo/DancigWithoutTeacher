#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode(1500, 1000), "선생님 몰래 춤추기");

	Texture background;

	background.loadFromFile("image/background.png");

	Sprite backgroundImg(background);

	// 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
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

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
	

		window.display();
	}
}
