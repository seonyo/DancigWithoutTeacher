#include "all.h"

void teacherSelect() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\JalnanGothicTTF.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	Texture background;
	Texture teacherContent;

	background.loadFromFile("image/background.png");
	teacherContent.loadFromFile("image/teacherContent.png");

	Sprite backgroundImg(background);
	Sprite contentImg(teacherContent);

	// 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	contentImg.setPosition(520, 220);

	//지우T
	CircleShape jwpShape(130);
	jwpShape.setFillColor(Color(255, 255, 255));
	jwpShape.setPosition(130, 360);

	Text jwpText(L"지우T", font, 28);
	jwpText.setFillColor(Color(255, 255, 255));
	jwpText.setPosition(220, 630);


	//재민T
	CircleShape ljmShape(130);
	ljmShape.setFillColor(Color(255, 255, 255));
	ljmShape.setPosition(450, 360);

	Text ljmText(L"재민T", font, 28);
	ljmText.setFillColor(Color(255, 255, 255));
	ljmText.setPosition(540, 630);

	//영철T
	CircleShape kycShape(130);
	kycShape.setFillColor(Color(255, 255, 255));
	kycShape.setPosition(770, 360);

	Text kycText(L"영철T", font, 28);
	kycText.setFillColor(Color(255, 255, 255));
	kycText.setPosition(860, 630);

	//명수T
	CircleShape smsShape(130);
	smsShape.setFillColor(Color(255, 255, 255));
	smsShape.setPosition(1090, 360);

	Text smsText(L"명수T", font, 28);
	smsText.setFillColor(Color(255, 255, 255));
	smsText.setPosition(1180, 630);

	//다음으로 버튼 생성 및 설정
	RectangleShape startBtn(Vector2f(220, 70));
	startBtn.setFillColor(Color(0, 99, 28));
	startBtn.setPosition(1150, 810);

	Text startBtnText(L"게임시작", font, 30);
	startBtnText.setFillColor(Color(255, 255, 255));
	startBtnText.setPosition(1200, 827);

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
					gamePlay();
				}
			}

		}

		window.draw(backgroundImg);
		window.draw(contentImg);
		window.draw(jwpShape);
		window.draw(ljmShape);
		window.draw(kycShape);
		window.draw(smsShape);
		window.draw(jwpText);
		window.draw(ljmText);
		window.draw(kycText);
		window.draw(smsText);
		window.draw(startBtn);
		window.draw(startBtnText);

		window.display();
	}
}
