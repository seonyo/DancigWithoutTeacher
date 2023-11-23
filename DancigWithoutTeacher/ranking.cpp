#include "all.h"
#include "Database.h"

void ranking() {

	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	if (!connectToDatabase()) {
		cout << "데이터베이스 연결 실패" << endl;
		// 데이터베이스 연결 실패 처리
		return;
	}

	Texture background;
	Texture rankigContent;

	background.loadFromFile("image/RankingBackground.png");
	rankigContent.loadFromFile("image/rankingContent.png");

	Sprite backgroundImg(background);

	RectangleShape rankingBackground;

	// 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);


	//db에서 랭킹 select
	const char* Query = "SELECT * FROM info ORDER BY score DESC limit 5";
	Stat = mysql_query(ConnPtr, Query);

	int rowCount = 0;
	int recY = 200;

	Result = mysql_store_result(ConnPtr);		//결과 확인하기
	while ((Row = mysql_fetch_row(Result)) != NULL) {
		printf("%s %s %s\n", Row[0], Row[1], Row[2]);
	}
	mysql_free_result(Result);

	closeDatabase();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

		}
		window.draw(backgroundImg);

		window.display();
	}
}