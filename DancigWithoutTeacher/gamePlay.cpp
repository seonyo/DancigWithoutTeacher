#include "all.h"
#include <random>

random_device rng;

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");
	int score = 0;

	Font font;
	Music music;
	Texture background;
	Texture teacher;
	Texture teacher_back;
	Texture teacher_side;
	Texture Studnet;
	Texture Stu1_front;
	Texture Stu1_back;
	Texture Stu2_front;
	Texture Stu2_back;
	Texture Stu3_front;
	Texture Stu3_back;

	uniform_real_distribution<double> dist1(1.0, 4.0);		// 뒤 돌아보고 있을 때의 난수
	uniform_real_distribution<double> dist2(1.0, 6.0);		// 앞을 보고 있을 때의 난수
	

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("폰트 불러오기 실패");
	}

	if (!music.openFromFile("music/몽키매직.wav")) {
		cout << "음원 파일을 열 수 없습니다" << endl;
		return;
	}


	// 이미지 불러오기
	background.loadFromFile("image/GamePlayBackground.png");		//배경 이미지
	teacher.loadFromFile("image/SMS.png");		// 명수 정면 이미지
	teacher_back.loadFromFile("image/SMS_Back.png");	//명수 뒷모습 이미지
	teacher_side.loadFromFile("image/SMS_Side.png");		//명수 앞모습 이미지
	Stu1_front.loadFromFile("image/Stu1-1.png");
	Stu1_back.loadFromFile("image/Stu1-2.png");
	Stu2_front.loadFromFile("image/Stu2-1.png");
	Stu2_back.loadFromFile("image/Stu2-2.png");
	Stu3_front.loadFromFile("image/Stu3-1.png");
	Stu3_back.loadFromFile("image/Stu3-2.png");
	Studnet.loadFromFile("image/Stu.png");

	Sprite backgroundImg(background);
	Sprite teacherImg(teacher_back);
	Sprite Student1Img(Stu1_front);
	Sprite Student2Img(Stu2_front);
	Sprite Student3Img(Stu3_front);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);


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


	bool showTeacher = false;
	float showTeacherTimer = 0.0f;
	teacherImg.setPosition(1100, 80);
	teacherImg.setScale(1.3, 1.4);

	float teacherSideTime = 0.25f; 
	bool showTeacherSide = false;
	float showTeacherSideTimer = 0.0f;

	float teacherBackTime = dist1(rng);
	float teacherFrontTime = dist2(rng);

	float studentTime = 0.0f;
	float spaceTime = 0.0f;

	bool isTeacherVisible = false;
	bool isSpaceTime = false;

	Student1Img.setPosition(85, 430);
	Student1Img.setScale(1.8, 2.1);

	Student2Img.setPosition(550, 430);
	Student2Img.setScale(1.8, 2.1);


	Student3Img.setPosition(1015, 430);
	Student3Img.setScale(1.8, 2.1);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		float elapsedTime = clock.restart().asSeconds();		//시간 측정 변수(초 단위)
		float timebarWidth = (timeRemaining / totalTime) * 800;		//800으로 시작해서 비율만큼 계산
		timeBar.setSize(Vector2f(timebarWidth, 80));		// 타임바 크기 설정

		if (!showTeacher && showTeacherTimer >= teacherBackTime) {
			// 선생님 이미지를 옆모습으로 변경하고 타이머 초기화
			showTeacher = true;
			teacherImg.setTexture(teacher_side);
			showTeacherTimer = 0.0f;

			// 아직 옆모습을 보이지 않았다면
			if (!showTeacherSide) {
				// 플래그 설정 및 타이머 초기화
				showTeacherSide = true;
				showTeacherSideTimer = 0.0f;  // Reset timer
			}
		}

		//뒷모습 타이머 업데이트
		showTeacherTimer += elapsedTime;

		if (showTeacherSide) {
			// 옆모습 이미지의 타이머 업데이트
			showTeacherSideTimer += elapsedTime;
		}

		// 0.3초가 지나면 앞모습
		if (showTeacherSide && showTeacherSideTimer >= teacherSideTime) {
			teacherImg.setTexture(teacher);
			showTeacherSide = false;
			isTeacherVisible = true;
		}

		if (showTeacher && showTeacherTimer >= teacherFrontTime) {
			showTeacher = false;
			isTeacherVisible = false;
			teacherImg.setTexture(teacher_back);
			showTeacherTimer = 0.0f;  // 타이머 초기화
			teacherBackTime = dist1(rng);  // 다음 teacher_back 이미지가 나타날 랜덤 시간 생성
		}

		if (!isTeacherVisible) {
			studentTime += elapsedTime;
			if (studentTime > 0.2) {
				Student1Img.setTexture(Stu1_back);
				Student2Img.setTexture(Stu2_back);
			}

			if (studentTime > 0.4) {
				Student1Img.setTexture(Stu1_front);
				Student2Img.setTexture(Stu2_front);
				studentTime = 0.0;
			}
		}
		else {
			Student1Img.setTexture(Studnet);
			Student2Img.setTexture(Studnet);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!isSpacePressed) {
				isSpacePressed = true;
				music.play();		//음악 시작
			}
			timeRemaining += elapsedTime;		//스페이스를 누르면 증가

			spaceTime += elapsedTime;
			if (spaceTime > 0.2) {
					Student3Img.setTexture(Stu3_front);
			}

			if (spaceTime > 0.4) {
				Student3Img.setTexture(Stu3_back);
				spaceTime = 0.0;
			}
		}
		else {
			isSpacePressed = false;
			timeRemaining -= elapsedTime;		//스페이스를 누르면 증가
			music.stop();		//음악 종료

			Student3Img.setTexture(Studnet);
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
		window.draw(Student1Img);
		window.draw(Student2Img);
		window.draw(Student3Img);
;		window.draw(scoreText);

		window.display();
	}
}