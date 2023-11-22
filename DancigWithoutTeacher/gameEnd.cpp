#include "all.h"


int scroe = 0;
void gameEnd(int score) {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");
	Font font;

	if (!font.loadFromFile("Font/KimjungchulMyungjo-Bold.ttf"))
	{
		cout << "��Ʈ�� �ҷ����� �� �����߽��ϴ�." << endl;
	}

	Texture background;
	background.loadFromFile("image/GameEndBackground.png");

	Sprite backgroundImg(background);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	Text socreTextContent(L"����� ������?", font, 55);
	socreTextContent.setPosition(180, 240);
	socreTextContent.setFillColor(Color(0, 0, 0));

	Text scoreText(to_string(score), font, 90);
	scoreText.setPosition(580, 210);
	scoreText.setFillColor(Color(50, 99, 159));

	Text gameOverText(L"ĥ�� ������ ĥ��~", font, 90);
	gameOverText.setPosition(180, 400);
	gameOverText.setFillColor(Color(196, 0, 0));


	//��ư ����
	RectangleShape rankingBtn(Vector2f(220, 70));
	rankingBtn.setFillColor(Color(0, 99, 28));
	rankingBtn.setPosition(180, 600);


	Text rankingBtnText(L"��ŷ����", font, 30);
	rankingBtnText.setFillColor(Color(255, 255, 255));
	rankingBtnText.setPosition(233, 618);

	RectangleShape mainBtn(Vector2f(220, 70));
	mainBtn.setFillColor(Color(0, 99, 28));
	mainBtn.setPosition(450, 600);

	Text mainBtnText(L"��������", font, 30);
	mainBtnText.setFillColor(Color(255, 255, 255));
	mainBtnText.setPosition(503, 618);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (rankingBtn.getGlobalBounds().contains(mousePos)) {
					window.close();
					ranking();
				}
				if (mainBtn.getGlobalBounds().contains(mousePos)) {
					window.close();
					home();
				}
			}

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
		window.draw(socreTextContent);
		window.draw(scoreText);
		window.draw(gameOverText);
		window.draw(rankingBtn);
		window.draw(rankingBtnText);
		window.draw(mainBtn);
		window.draw(mainBtnText);

		window.display();
	}
}