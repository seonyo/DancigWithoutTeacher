#include "all.h"
#include "teacher.h"
#include <random>

class GamePlay {
private:

    // 멤버변수 초기화
    RenderWindow window;
    Font font;
    Music music;
    Texture background;
    Texture Studnet;
    Texture Stu1_front;
    Texture Stu1_back;
    Texture Stu2_front;
    Texture Stu2_back;
    Texture Stu3_front;
    Texture Stu3_back;

    Sprite backgroundImg;
    Sprite Student1Img;
    Sprite Student2Img;
    Sprite Student3Img;

    RectangleShape timeBar;
    Text scoreText;

    Clock clock;
    float totalTime;
    float timeRemaining;
    float scoreTimer;

    bool isSpacePressed;
    float studentTime;
    float spaceTime;
    bool isTeacherVisible;
    bool isSpaceTime;
    int score;

    teacher teacher; 

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
        Stu1_front.loadFromFile("image/Stu1-1.png");
        Stu1_back.loadFromFile("image/Stu1-2.png");
        Stu2_front.loadFromFile("image/Stu2-1.png");
        Stu2_back.loadFromFile("image/Stu2-2.png");
        Stu3_front.loadFromFile("image/Stu3-1.png");
        Stu3_back.loadFromFile("image/Stu3-2.png");
        Studnet.loadFromFile("image/Stu.png");

        backgroundImg.setTexture(background);
        Student1Img.setTexture(Stu1_front);
        Student2Img.setTexture(Stu2_front);
        Student3Img.setTexture(Stu3_front);

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

        Student1Img.setPosition(85, 430);
        Student1Img.setScale(1.8, 2.0);

        Student2Img.setPosition(550, 430);
        Student2Img.setScale(1.8, 2.0);

        Student3Img.setPosition(1015, 430);
        Student3Img.setScale(1.8, 2.);

        totalTime = 17.0f;
        timeRemaining = totalTime;
        scoreTimer = 0.0f;
        isSpacePressed = false;
        //teacherBackTime = dist1(rng);
        //teacherFrontTime = dist2(rng);
        studentTime = 0.0f;
        spaceTime = 0.0f;
        isSpaceTime = false;
        score = 0;

        random_device rng;
        uniform_real_distribution<double> dist1;
        uniform_real_distribution<double> dist2;

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
            timeRemaining -= elapsedTime;
            music.stop();
            Student3Img.setTexture(Studnet);
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
        window.draw(Student1Img);
        window.draw(Student2Img);
        window.draw(Student3Img);
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