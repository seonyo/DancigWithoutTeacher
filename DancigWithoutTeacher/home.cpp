#include "all.h"

void home() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	Font font;

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		cout << "폰트를 불러오는 데 실패했습니다." << endl;
	}

	Texture background;
	Texture mainContent;

	background.loadFromFile("image/background.png");
	mainContent.loadFromFile("image/mainContent.png");

	Sprite backgroundImg(background);
	Sprite mainContentImg(mainContent);

	mainContentImg.setPosition(900, 500);

	// 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);
	mainContentImg.setScale(
		500.0f / mainContent.getSize().x,
		240.0f / mainContent.getSize().y
	);

	//버튼 생성
	RectangleShape rankingBtn(Vector2f(220, 70));
	rankingBtn.setFillColor(Color(0, 0, 0, 0));
	rankingBtn.setPosition(900, 770);
	rankingBtn.setOutlineColor(Color(255, 255, 255));
	rankingBtn.setOutlineThickness(3);

	Text rankingBtnText(L"랭킹보기", font, 30);
	rankingBtnText.setFillColor(Color(255, 255, 255));
	rankingBtnText.setPosition(947, 785);

	RectangleShape startBtn(Vector2f(220, 70));
	startBtn.setFillColor(Color(0, 99, 28));
	startBtn.setPosition(1150, 770);
	startBtn.setOutlineColor(Color(0, 99, 28));
	startBtn.setOutlineThickness(3);

	Text startBtnText(L"게임시작", font, 30);
	startBtnText.setFillColor(Color(255, 255, 255));
	startBtnText.setPosition(1200, 785);



	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (startBtn.getGlobalBounds().contains(mousePos)) {
					cout << "눌러졌댜능" << endl;
					window.close();
					name();
				}
				if (rankingBtn.getGlobalBounds().contains(mousePos)) {
					window.close();
					ranking();
				}
			}

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
		window.draw(mainContentImg);
		window.draw(rankingBtn);
		window.draw(rankingBtnText);
		window.draw(startBtn);
		window.draw(startBtnText);

		window.display();
	}
}