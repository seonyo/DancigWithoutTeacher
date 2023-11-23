#include "all.h"
#include "Database.h"

void ranking() {
    RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

    if (!connectToDatabase()) {
        cout << "데이터베이스 연결 실패" << endl;
        // 데이터베이스 연결 실패 처리
        return;
    }

    Font font;
    if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
    {
        cout << "폰트를 불러오는 데 실패했습니다." << endl;
    }

    Texture background;
    background.loadFromFile("image/RankingBackground.png");
    Sprite backgroundImg(background);

    Texture arrow;
    arrow.loadFromFile("image/arrow.png");
    Sprite arrowImg(arrow);

    arrowImg.setPosition(100, 100);
    arrowImg.setScale(1.8, 1.8);


    // 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
    backgroundImg.setScale(
        static_cast<float>(window.getSize().x) / background.getSize().x,
        static_cast<float>(window.getSize().y) / background.getSize().y
    );

    //db에서 랭킹 select
    const char* Query = "SELECT * FROM info ORDER BY score DESC limit 5";
    Stat = mysql_query(ConnPtr, Query);

    int recY = 268;

    window.clear();

    window.draw(backgroundImg);

    Result = mysql_store_result(ConnPtr); // 결과 확인하기

    while ((Row = mysql_fetch_row(Result)) != NULL) {
        printf("%s %s %s\n", Row[0], Row[1], Row[2]);

        Text nameText(Row[1], font, 35);
        nameText.setFillColor(Color(0, 0, 0));
        nameText.setPosition(710, recY);

        window.draw(nameText);

        Text numberText(Row[2], font, 35);
        numberText.setFillColor(Color(0, 99, 28));
        numberText.setPosition(1100, recY);
        recY += 144;

        window.draw(numberText);
    }

    mysql_free_result(Result);
    closeDatabase();

    window.draw(arrowImg);

    window.display();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                if (arrowImg.getGlobalBounds().contains(mousePos)) {
                    window.close();
                    home();
                }
            }

        }
    }
}
