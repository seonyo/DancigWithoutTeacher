#include "all.h"
#include "StringResource.h"
#include "Database.h"
#include "gamePlay.cpp"
#include <Windows.h>

string inputString;

void name() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"선생님 몰래 춤추기");

	if (!connectToDatabase()) {
		cout << "데이터베이스 연결 실패" << endl;
		// 데이터베이스 연결 실패 처리
		return;
	}

	Font font;

	if (!font.loadFromFile("Font/JalnanGothicTTF.ttf"))
	{
		printf("폰트 불러오기 실패");
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

	//inputText 설정
	Text inputText;
	inputText.setFont(font);
	inputText.setCharacterSize(38);	//size 설정
	inputText.setFillColor(Color(0, 99, 28));
	inputText.setPosition(395, 465);


	//inputText 배경설정
	RectangleShape inputBackground(Vector2f(800, 80));
	inputBackground.setFillColor(Color(255, 255, 255));
	inputBackground.setPosition(380, 450);

	//idContent 설정
	contentImg.setPosition(520, 380);

	//게임시작 버튼 생성 및 설정
	RectangleShape nextBtn(Vector2f(220, 70));
	nextBtn.setFillColor(Color(0, 99, 28));
	nextBtn.setPosition(1150, 810);

	Text nextBtnText(L"게임시작", font, 30);
	nextBtnText.setFillColor(Color(255, 255, 255));
	nextBtnText.setPosition(1200, 827);


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::TextEntered) {	//text를 눌렀을 대
				if (event.text.unicode < 128) {		//unicode가 128 이하이면
					if (event.text.unicode == 8 && !inputString.empty()) {		//empty가 비지 않고, bacakspace를 눌렀으면
						inputString.pop_back();		// pop 하기
					}
					else {
						inputString += static_cast<char>(event.text.unicode);	//아니면 inputString에 추가하기, static_cast는 형변환
					}
					inputText.setString(inputString);	//inputText에 inputString 넣기
				}
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (inputString == "") {
					MessageBox(NULL, L"닉네임을 입력하세요", L"경고", MB_OK);
				}
				else {
					if (nextBtn.getGlobalBounds().contains(mousePos)) {
						string query = "INSERT INTO info (name) VALUES ('" + inputString + "')";
						const char* Query = query.c_str();		// C Style 문자열로 변환하기 (mysql 쿼리문에선 C스타일만 받기 때문)
						Stat = mysql_query(ConnPtr, Query);		//쿼리문 성공여부

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