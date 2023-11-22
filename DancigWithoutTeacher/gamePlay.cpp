#include "all.h"
#include <random>

random_device rng;

void gamePlay() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");
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

	uniform_real_distribution<double> dist1(1.0, 4.0);		// �� ���ƺ��� ���� ���� ����
	uniform_real_distribution<double> dist2(1.0, 6.0);		// ���� ���� ���� ���� ����
	

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
	}

	if (!music.openFromFile("music/��Ű����.wav")) {
		cout << "���� ������ �� �� �����ϴ�" << endl;
		return;
	}


	// �̹��� �ҷ�����
	background.loadFromFile("image/GamePlayBackground.png");		//��� �̹���
	teacher.loadFromFile("image/SMS.png");		// ��� ���� �̹���
	teacher_back.loadFromFile("image/SMS_Back.png");	//��� �޸�� �̹���
	teacher_side.loadFromFile("image/SMS_Side.png");		//��� �ո�� �̹���
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
	float totalTime = 17.0f;		//17�� ���� ���� (1�ʿ� 1f�� ����)
	float timeRemaining = totalTime;
	float scoreTimer = 0.0f; //�ð� ���� ����

	bool isSpacePressed = false;		//�����̽� ���� ����


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

		float elapsedTime = clock.restart().asSeconds();		//�ð� ���� ����(�� ����)
		float timebarWidth = (timeRemaining / totalTime) * 800;		//800���� �����ؼ� ������ŭ ���
		timeBar.setSize(Vector2f(timebarWidth, 80));		// Ÿ�ӹ� ũ�� ����

		if (!showTeacher && showTeacherTimer >= teacherBackTime) {
			// ������ �̹����� ��������� �����ϰ� Ÿ�̸� �ʱ�ȭ
			showTeacher = true;
			teacherImg.setTexture(teacher_side);
			showTeacherTimer = 0.0f;

			// ���� ������� ������ �ʾҴٸ�
			if (!showTeacherSide) {
				// �÷��� ���� �� Ÿ�̸� �ʱ�ȭ
				showTeacherSide = true;
				showTeacherSideTimer = 0.0f;  // Reset timer
			}
		}

		//�޸�� Ÿ�̸� ������Ʈ
		showTeacherTimer += elapsedTime;

		if (showTeacherSide) {
			// ����� �̹����� Ÿ�̸� ������Ʈ
			showTeacherSideTimer += elapsedTime;
		}

		// 0.3�ʰ� ������ �ո��
		if (showTeacherSide && showTeacherSideTimer >= teacherSideTime) {
			teacherImg.setTexture(teacher);
			showTeacherSide = false;
			isTeacherVisible = true;
		}

		if (showTeacher && showTeacherTimer >= teacherFrontTime) {
			showTeacher = false;
			isTeacherVisible = false;
			teacherImg.setTexture(teacher_back);
			showTeacherTimer = 0.0f;  // Ÿ�̸� �ʱ�ȭ
			teacherBackTime = dist1(rng);  // ���� teacher_back �̹����� ��Ÿ�� ���� �ð� ����
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
				music.play();		//���� ����
			}
			timeRemaining += elapsedTime;		//�����̽��� ������ ����

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
			timeRemaining -= elapsedTime;		//�����̽��� ������ ����
			music.stop();		//���� ����

			Student3Img.setTexture(Studnet);
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
		window.draw(Student1Img);
		window.draw(Student2Img);
		window.draw(Student3Img);
;		window.draw(scoreText);

		window.display();
	}
}