#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");
	int score = 0;

	Font font;
	Music music;
	Texture background;
	Texture teacher;
	

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
	}

	if (!music.openFromFile("music/��Ű����.wav")) {
		cout << "���� ������ �� �� �����ϴ�" << endl;
		return;
	}

	background.loadFromFile("image/GamePlayBackground.png");
	teacher.loadFromFile("image/SMS.png");

	Sprite backgroundImg(background);
	Sprite teacherImg(teacher);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	teacherImg.setPosition(1000, 100);
	teacherImg.setScale(1.8, 1.9);

	RectangleShape timeBar(Vector2f(800, 80));
	timeBar.setFillColor(Color(50, 99, 159));
	timeBar.setPosition(14, 20);

	Text scoreText(to_string(score), font, 50);
	scoreText.setPosition(1300, 28);
	scoreText.setFillColor(Color(50, 99, 159));

	Clock clock;
	float totalTime = 17.0f;		//17�� ���� ���� (1�ʿ� 1f�� ����)
	float timeRemaining = totalTime;
	float scoreTimer = 0.0f; //�ð� ���� ����

	bool isSpacePressed = false;		//�����̽� ���� ����

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();		//�ð� ���� ����(�� ����)
		float timebarWidth = (timeRemaining / totalTime) * 800;		//800���� �����ؼ� ������ŭ ���
		timeBar.setSize(Vector2f(timebarWidth, 80));

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!isSpacePressed) {
				isSpacePressed = true;
				music.play();		//���� ����
			}
			timeRemaining += elapsedTime;		//�����̽��� ������ ����
		}
		else {
			isSpacePressed = false;
			timeRemaining -= elapsedTime;		//�����̽��� ������ ����
			music.stop();		//���� ����
		}

		timebarWidth = (timeRemaining / totalTime) * 800;		//Timebar ���� �缳��
		// timebarWidth�� 800���� ũ�� ��� ���� �ʱ�ȭ
		if (timebarWidth > 800) {
			timeRemaining = 17.0f;
			totalTime = 17.0f;
			timebarWidth = 800;
		}
		timeBar.setSize(Vector2f(timebarWidth, 80));

		// 0.1�ʰ� ���� ������ score 1�� ����
		scoreTimer += elapsedTime;
		if (scoreTimer >= 0.1f) {
			score++;
			scoreText.setString(to_string(score)); // scoreText ������Ʈ
			scoreTimer = 0.0f; // Ÿ�̸� �ʱ�ȭ
		}


		if (timeRemaining <= 0) {
			cout << "Ÿ�Ӿƿ�����" << endl;
			window.close();
;			gameEnd();
		} 

		window.clear(Color::Black);
		
		window.draw(backgroundImg);
		window.draw(timeBar);
		window.draw(teacherImg);
		window.draw(scoreText);

		window.display();
	}
}