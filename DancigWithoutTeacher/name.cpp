#include "all.h"
#include "StringResource.h"
#include "Database.h"
#include "gamePlay.cpp"
#include <Windows.h>

string inputString;

void name() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	if (!connectToDatabase()) {
		cout << "�����ͺ��̽� ���� ����" << endl;
		// �����ͺ��̽� ���� ���� ó��
		return;
	}

	Font font;

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
	}

	Texture background;
	Texture nameContent;

	background.loadFromFile("image/background.png");
	nameContent.loadFromFile("image/idContent.png");

	Sprite backgroundImg(background);
	Sprite contentImg(nameContent);

	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);

	//inputText ����
	Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(38);	//size ����
	inputText.setFillColor(Color(0, 99, 28));
	inputText.setPosition(395, 465);


	//inputText ��漳��
	RectangleShape inputBackground(Vector2f(800, 80));
	inputBackground.setFillColor(Color(255, 255, 255));
	inputBackground.setPosition(380, 450);

	//idContent ����
	contentImg.setPosition(520, 380);

	//���ӽ��� ��ư ���� �� ����
	RectangleShape nextBtn(Vector2f(220, 70));
	nextBtn.setFillColor(Color(0, 99, 28));
	nextBtn.setPosition(1150, 810);

	Text nextBtnText(L"���ӽ���", font, 30);
	nextBtnText.setFillColor(Color(255, 255, 255));
	nextBtnText.setPosition(1200, 827);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::TextEntered) {	//text�� ������ ��
				if (event.text.unicode < 128) {		//unicode�� 128 �����̸�
					if (event.text.unicode == 8 && !inputString.empty()) {		//empty�� ���� �ʰ�, bacakspace�� ��������
						inputString.pop_back();		// pop �ϱ�
					}
					else {
						inputString += static_cast<char>(event.text.unicode);	//�ƴϸ� inputString�� �߰��ϱ�, static_cast�� ����ȯ
					}
					inputText.setString(inputString);	//inputText�� inputString �ֱ�
				}
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (inputString == "") {
					MessageBox(NULL, L"�г����� �Է��ϼ���", L"���", MB_OK);
				}
				else {
					if (nextBtn.getGlobalBounds().contains(mousePos)) {
						string query = "INSERT INTO info (name) VALUES ('" + inputString + "')";
						const char* Query = query.c_str();		// C Style ���ڿ��� ��ȯ�ϱ� (mysql ���������� C��Ÿ�ϸ� �ޱ� ����)
						Stat = mysql_query(ConnPtr, Query);		//������ ��������

						mysql_close(ConnPtr);
						window.close();
						GamePlay game;
						game.run();
					}
				}
			}
		}

		window.clear(Color::Black);
		window.draw(backgroundImg);
		window.draw(inputBackground);
		window.draw(inputText);
		window.draw(contentImg);
		window.draw(nextBtn);
		window.draw(nextBtnText);

		window.display();
	}
}