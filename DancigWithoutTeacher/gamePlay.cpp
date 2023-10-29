#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\H2HDRM.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
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
			cout << "Ÿ�Ӿƿ�����" << endl;
			window.close();
;			gameEnd();
		}

		window.clear(Color::Black);

		window.draw(timeBar);

		window.display();
	}
}