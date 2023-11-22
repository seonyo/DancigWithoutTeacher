#include "all.h"

int scroe = 0;
void gameEnd(int score) {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");
	Font font;

	if (!font.loadFromFile("Font/KimjungchulMyungjo-Bold.ttf"))
	{
		cout << "폰트를 불러오는 데 실패했습니다." << endl;
	}

	Texture background;
	background.loadFromFile("image/GameEndBackground.png");

	Sprite backgroundImg(background);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);


	cout << score << endl;

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