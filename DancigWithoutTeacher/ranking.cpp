#include "all.h"

void ranking() {

	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	//DB ����
	MYSQL Conn;		//db ������ ��� ��
	MYSQL* ConnPtr = NULL;		//db �ڵ�
	MYSQL_RES* Result;		// ���� ������ ����� ��� ����ü ������
	MYSQL_ROW Row;		//���� ������ ����� ���� ���� ������ ��� ����ü
	int Stat;		// ������û �� ��� (����, ����)

	mysql_init(&Conn);		//���� �ʱ�ȭ

	ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "990327", "DancingWithoutTeacher", 3306, (char*)NULL, 0);

	if (ConnPtr == NULL) {
		fprintf(stderr, "MYsql connection error : %s", mysql_error(&Conn));
	}
	else {
		printf("���� ����...\n");
	}

	Texture background;

	background.loadFromFile("image/background.png");

	Sprite backgroundImg(background);

	// �̹��� ũ�⸦ â ũ�⿡ �°� ���� (���� ���)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	//�ѱ� ���� ����
	mysql_query(ConnPtr, "set session character_set_connection=euckr;");
	mysql_query(ConnPtr, "set session character_set_results=euckr;");
	mysql_query(ConnPtr, "set session character_set_client=euckr;");

	const char* Query = "SELECT * FROM info ORDER BY score DESC";
	Stat = mysql_query(ConnPtr, Query);
	if (stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&Conn));
	}


	Result = mysql_store_result(ConnPtr);		//��� Ȯ���ϱ�
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