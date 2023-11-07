#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	Font font;
	Music music;
	
	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
	}

	if (!music.openFromFile("music/��Ű����.wav")) {
		cout << "���� ������ �� �� �����ϴ�" << endl;
		return;
	}

	RectangleShape timeBar(Vector2f(800, 80));
	timeBar.setFillColor(Color(0, 99, 28));
	timeBar.setPosition(20, 100);

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
			cout << "Ÿ�Ӿƿ�����" << endl;
			window.close();
;			gameEnd();
		}

		window.clear(Color::Black);

		window.draw(timeBar);

		window.display();
	}
}