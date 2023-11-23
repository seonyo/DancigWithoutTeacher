#include "all.h"
#include "teacher.h"
#include "student.h"
#include <random>

class GamePlay {
private:

    // 멤버변수 초기화
    RenderWindow window;
    Font font;
    Music music;
    Texture background;

    Sprite backgroundImg;
  
    RectangleShape timeBar;
    Text scoreText;

    Clock clock;
    float totalTime;
    float timeRemaining;
    float scoreTimer;

    bool isSpacePressed;
    float spaceTime;
    bool isTeacherVisible;
    bool isSpaceTime;
    int score;

    teacher teacher; 
    student student;

    random_device rng;
    uniform_real_distribution<double> dist1;
    uniform_real_distribution<double> dist2;

public:
    GamePlay() : dist1(1.0, 5.0), dist2(1.0, 6.0) {
        initialize();
    }

    void initialize() {
        window.create(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

        if (!font.loadFromFile("Font/JalnanGothicTTF.ttf")) {
            printf("폰트 불러오기 실패");
        }

        if (!music.openFromFile("music/몽키매직.wav")) {
            cout << "음원 파일을 열 수 없습니다" << endl;
            return;
        }

        // 이미지 불러오기
        background.loadFromFile("image/GamePlayBackground.png");

        backgroundImg.setTexture(background);

        backgroundImg.setScale(
            static_cast<float>(window.getSize().x) / background.getSize().x,
            static_cast<float>(window.getSize().y) / background.getSize().y
        );

        timeBar.setSize(Vector2f(800, 80));
        timeBar.setFillColor(Color(50, 99, 159));
        timeBar.setPosition(14, 20);

        scoreText.setFont(font);
        scoreText.setCharacterSize(50);
        scoreText.setPosition(1300, 28);
        scoreText.setFillColor(Color(50, 99, 159));

        totalTime = 17.0f;
        timeRemaining = totalTime;
        scoreTimer = 0.0f;
        isSpacePressed = false;

        spaceTime = 0.0f;
        isSpaceTime = false;
        score = 0;

        random_device rng;
        uniform_real_distribution<double> dist1;
        uniform_real_distribution<double> dist2;

        student.initiallize();
        teacher.teacherTurnTime(0.0);
    }

    void handleInput() {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        float elapsedTime = clock.restart().asSeconds();
        float timebarWidth = (timeRemaining / totalTime) * 800;
        timeBar.setSize(Vector2f(timebarWidth, 80));

        teacher.teacherTurnTime(elapsedTime);
        student.studentMove(elapsedTime, isTeacherVisible);

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (isTeacherVisible) {
                music.stop();
                window.close();
                gameEnd(score);
            }
            if (!isSpacePressed) {
                isSpacePressed = true;
                music.play();
            }
            timeRemaining += elapsedTime;

            spaceTime += elapsedTime;
            student.isSpaceStudent(spaceTime);

        }
        else {
            isSpacePressed = false;
            timeRemaining -= elapsedTime;
            music.stop();
            student.isNotSpaceStudent();
        }

        timebarWidth = (timeRemaining / totalTime) * 800;
        if (timebarWidth > 800) {
            timeRemaining = 17.0f;
            totalTime = 17.0f;
            timebarWidth = 800;
        }
        timeBar.setSize(Vector2f(timebarWidth, 80));

        scoreTimer += elapsedTime;
        if (scoreTimer >= 0.1f) {
            score++;
            scoreText.setString(to_string(score));
            scoreTimer = 0.0f;
        }

        if (timeRemaining <= 0) {
            cout << "타임아웃오바" << endl;
            music.stop();

            window.close();
            gameEnd(score);
        }
    }

    void render() {

        window.clear(Color::Black);

        window.draw(backgroundImg);
        window.draw(timeBar);
        window.draw(student.getStudent1Sprite());
        window.draw(student.getStudent2Sprite());
        window.draw(student.getStudent3Sprite());
        window.draw(scoreText);

        window.display();
    }

    void run() {
        while (window.isOpen()) {
            handleInput();
            render();
        }
    }

};