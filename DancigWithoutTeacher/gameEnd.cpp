#include "all.h"
#include "StringResource.h"
#include "Database.h"

//전역변수 score 생성
int scroe = 0;

void gameEnd(int score) {

	if (!connectToDatabase()) {
		cout << "데이터베이스 연결 실패" << endl;
		return;
	}

	string query = "UPDATE info SET score = '" + to_string(score) + "' WHERE name = '" + inputString + "'";
	const char* Query = query.c_str();		// C Style 문자열로 변환하기 (mysql 쿼리문에선 C스타일만 받기 때문)
	Stat = mysql_query(ConnPtr, Query);		//쿼리문 성공여부
	
	inputString = "";

	//쿼리문이 실패했다면 에러 메세지 출력
	if (Stat != 0) {
		//stderr을 출력하려면 fprintf를 사용해야 함
		fprintf(stderr, "Mysql qerry error : %s\n", mysql_error(&Conn));
	}

	closeDatabase();

	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"선생님 몰래 춤추기");
	Font font;


	if (!font.loadFromFile("Font/KimjungchulMyungjo-Bold.ttf"))
	{
		cout << "폰트를 불러오는 데 실패했습니다." << endl;
	}

	Texture background;
	background.loadFromFile("image/GameEndBackground.png");

	Sprite backgroundImg(background);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	Text socreTextContent(L"당신의 점수는?", font, 55);
	socreTextContent.setPosition(180, 240);
	socreTextContent.setFillColor(Color(0, 0, 0));

	Text scoreText(to_string(score), font, 90);
	scoreText.setPosition(580, 210);
	scoreText.setFillColor(Color(50, 99, 159));

	Text gameOverText(L"칠판 보세요 칠판~", font, 90);
	gameOverText.setPosition(180, 400);
	gameOverText.setFillColor(Color(196, 0, 0));


	//버튼 생성
	RectangleShape rankingBtn(Vector2f(220, 70));
	rankingBtn.setFillColor(Color(0, 99, 28));
	rankingBtn.setPosition(180, 600);


	Text rankingBtnText(L"랭킹보기", font, 30);
	rankingBtnText.setFillColor(Color(255, 255, 255));
	rankingBtnText.setPosition(233, 618);

	RectangleShape mainBtn(Vector2f(220, 70));
	mainBtn.setFillColor(Color(0, 99, 28));
	mainBtn.setPosition(450, 600);

	Text mainBtnText(L"메인으로", font, 30);
	mainBtnText.setFillColor(Color(255, 255, 255));
	mainBtnText.setPosition(503, 618);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (rankingBtn.getGlobalBounds().contains(mousePos)) {
					window.close();
					ranking();
				}
				if (mainBtn.getGlobalBounds().contains(mousePos)) {
					window.close();
					home();
				}
			}

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
		window.draw(socreTextContent);
		window.draw(scoreText);
		window.draw(gameOverText);
		window.draw(rankingBtn);
		window.draw(rankingBtnText);
		window.draw(mainBtn);
		window.draw(mainBtnText);

		window.display();
	}
}