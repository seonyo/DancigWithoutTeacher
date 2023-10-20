#include "all.h"

void newWindow() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\H2HDRM.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	Texture background;
	background.loadFromFile("image/background.png");

	Sprite backgroundImg(background);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(24);
	inputText.setFillColor(Color::White);
	inputText.setPosition(50,100);
	string inputString;
	bool textEntered = false;

	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::TextEntered) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 8 && !inputString.empty()) {
						inputString.pop_back();
					}
					else {
						inputString += static_cast<char>(event.text.unicode);
					}
					inputText.setString(inputString);
					textEntered = true;
				}
			}
		}
		window.clear(Color::Black);
		window.draw(backgroundImg);
		window.draw(inputText);

		window.display();
	}
}