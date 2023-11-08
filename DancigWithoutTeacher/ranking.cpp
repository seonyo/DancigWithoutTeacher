#include "all.h"

void ranking() {

	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	//DB 연결
	MYSQL Conn;		//db 정보를 담는 것
	MYSQL* ConnPtr = NULL;		//db 핸들
	MYSQL_RES* Result;		// 쿼리 성공시 결과를 담는 구조체 포인터
	MYSQL_ROW Row;		//쿼리 성공시 결과로 나온 행의 정보를 담는 구조체
	int Stat;		// 쿼리요청 후 결과 (성공, 실패)

	mysql_init(&Conn);		//정보 초기화

	ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "990327", "DancingWithoutTeacher", 3306, (char*)NULL, 0);

	if (ConnPtr == NULL) {
		fprintf(stderr, "MYsql connection error : %s", mysql_error(&Conn));
	}
	else {
		printf("연결 성공...\n");
	}

	Texture background;

	background.loadFromFile("image/background.png");

	Sprite backgroundImg(background);

	// 이미지 크기를 창 크기에 맞게 조절 (비율 계산)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	//한글 깨짐 지원
	mysql_query(ConnPtr, "set session character_set_connection=euckr;");
	mysql_query(ConnPtr, "set session character_set_results=euckr;");
	mysql_query(ConnPtr, "set session character_set_client=euckr;");

	const char* Query = "SELECT * FROM info ORDER BY score DESC";
	Stat = mysql_query(ConnPtr, Query);
	if (stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&Conn));
	}


	Result = mysql_store_result(ConnPtr);		//결과 확인하기
	while ((Row = mysql_fetch_row(Result)) != NULL) {
		printf("%s %s %s\n", Row[0], Row[1], Row[2]);
	}
	mysql_free_result(Result);

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