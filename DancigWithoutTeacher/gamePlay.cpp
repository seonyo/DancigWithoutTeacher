#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\H2HDRM.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	RectangleShape timeBar(Vector2f(800, 80));
	timeBar.setFillColor(Color(0, 99, 28));
	timeBar.setPosition(20, 100);

	Clock clock;
	float totalTime = 17.0f;
	float timeRemaining = totalTime;
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();
		timeRemaining -= elapsedTime;

		float timebarWidth = (timeRemaining / totalTime) * 800;
		timeBar.setSize(Vector2f(timebarWidth, 80));

		if (timeRemaining <= 0) {
			cout << "타임아웃오바" << endl;
			window.close();
;			gameEnd();
		}

		window.clear(Color::Black);

		window.draw(timeBar);

		window.display();
	}
}