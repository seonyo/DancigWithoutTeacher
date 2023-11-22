#include "all.h"
#include "Database.h"

void ranking() {

	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	if (!connectToDatabase()) {
		cout << "�����ͺ��̽� ���� ����" << endl;
		// �����ͺ��̽� ���� ���� ó��
		return;
	}

	Texture background;
	Texture rankigContent;
	Texture contentBackground;

	background.loadFromFile("image/background.png");
	rankigContent.loadFromFile("image/rankingContent.png");
	contentBackground.loadFromFile("image/rankingContentBackground.png");

	Sprite backgroundImg(background);
	Sprite rankingContemtImg(rankigContent);
	Sprite contentBackgroundImg(contentBackground);

	// �̹��� ũ�⸦ â ũ�⿡ �°� ���� (���� ���)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	rankingContemtImg.setPosition(650, 100);

	//db���� ��ŷ select
	const char* Query = "SELECT * FROM info ORDER BY score DESC limit 5";
	Stat = mysql_query(ConnPtr, Query);

	Result = mysql_store_result(ConnPtr);		//��� Ȯ���ϱ�
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
		window.draw(rankingContemtImg);

		window.display();
	}
}