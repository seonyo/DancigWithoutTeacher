#include "all.h"

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");
	int score = 0;

	Font font;
	Music music;
	Texture background;
	Texture teacher;
	

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	if (!music.openFromFile("music/몽키매직.wav")) {
		cout << "음원 파일을 열 수 없습니다" << endl;
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
	float totalTime = 17.0f;		//17초 동안 실행 (1초에 1f씩 감소)
	float timeRemaining = totalTime;
	float scoreTimer = 0.0f; //시간 측정 변수

	bool isSpacePressed = false;		//스페이스 눌림 여부

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();		//시간 측정 변수(초 단위)
		float timebarWidth = (timeRemaining / totalTime) * 800;		//800으로 시작해서 비율만큼 계산
		timeBar.setSize(Vector2f(timebarWidth, 80));

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!isSpacePressed) {
				isSpacePressed = true;
				music.play();		//음악 시작
			}
			timeRemaining += elapsedTime;		//스페이스를 누르면 증가
		}
		else {
			isSpacePressed = false;
			timeRemaining -= elapsedTime;		//스페이스를 누르면 증가
			music.stop();		//음악 종료
		}

		timebarWidth = (timeRemaining / totalTime) * 800;		//Timebar 넓이 재설정
		// timebarWidth가 800보다 크면 모든 것을 초기화
		if (timebarWidth > 800) {
			timeRemaining = 17.0f;
			totalTime = 17.0f;
			timebarWidth = 800;
		}
		timeBar.setSize(Vector2f(timebarWidth, 80));

		// 0.1초가 지날 때마다 score 1씩 증가
		scoreTimer += elapsedTime;
		if (scoreTimer >= 0.1f) {
			score++;
			scoreText.setString(to_string(score)); // scoreText 업데이트
			scoreTimer = 0.0f; // 타이머 초기화
		}


		if (timeRemaining <= 0) {
			cout << "타임아웃오바" << endl;
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