#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	Font font;
	Music music;
	Texture background;

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	if (!music.openFromFile("music/몽키매직.wav")) {
		cout << "음원 파일을 열 수 없습니다" << endl;
		return;
	}

	background.loadFromFile("image/GamePlayBackground.png");

	Sprite backgroundImg(background);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	RectangleShape timeBar(Vector2f(800, 80));
	timeBar.setFillColor(Color(50, 99, 159));
	timeBar.setPosition(14, 20);

	Clock clock;
	float totalTime = 17.0f;
	float timeRemaining = totalTime;
	
	bool isSpacePressed = false;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();
		float timebarWidth = (timeRemaining / totalTime) * 800;
		timeBar.setSize(Vector2f(timebarWidth, 80));

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!isSpacePressed) {
				isSpacePressed = true;
				music.play();
			}
			timeRemaining += elapsedTime;
			timebarWidth = (timeRemaining / totalTime) * 800;
			if (timebarWidth > 800) {
				timebarWidth = 800;
			}
			timeBar.setSize(Vector2f(timebarWidth, 80));

		}

		else {
			timeRemaining -= elapsedTime;
			timebarWidth = (timeRemaining / totalTime) * 800;
			timeBar.setSize(Vector2f(timebarWidth, 80));

			isSpacePressed = false;
			music.stop();
		}


		if (timeRemaining <= 0) {
			cout << "타임아웃오바" << endl;
			window.close();
;			gameEnd();
		}

		window.clear(Color::Black);
		
		window.draw(backgroundImg);
		window.draw(timeBar);

		window.display();
	}
}