#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode(1500, 1000), L"������ ���� ���߱�");

	Font font;

	if (!font.loadFromFile("C:\\Windows\\Fonts\\H2HDRM.ttf"))
	{
		printf("��Ʈ �ҷ����� ����");
		return -1;
	}

	Texture background;
	Texture mainContent;

	background.loadFromFile("image/background.png");
	mainContent.loadFromFile("image/mainContent.png");

	Sprite backgroundImg(background);
	Sprite mainContentImg(mainContent);

	mainContentImg.setPosition(900, 500);

	// �̹��� ũ�⸦ â ũ�⿡ �°� ���� (���� ���)
	backgroundImg.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y
	);
	mainContentImg.setScale(
		500.0f / mainContent.getSize().x,
		240.0f / mainContent.getSize().y
	);

	//��ư ����
	RectangleShape rankingBtn(Vector2f(220, 70));
	rankingBtn.setFillColor(Color(0, 0, 0, 0));
	rankingBtn.setPosition(900, 770);
	rankingBtn.setOutlineColor(Color(255, 255, 255));
	rankingBtn.setOutlineThickness(3);

	Text rankingBtnText(L"��ŷ����", font, 30);
	rankingBtnText.setFillColor(Color(255,255,255));
	rankingBtnText.setPosition(947, 785);

	RectangleShape startBtn(Vector2f(220, 70));
	startBtn.setFillColor(Color(0,99,28));
	startBtn.setPosition(1150, 770);
	startBtn.setOutlineColor(Color(0, 99, 28));
	startBtn.setOutlineThickness(3);

	Text startBtnText(L"���ӽ���", font, 30);
	startBtnText.setFillColor(Color(255, 255, 255));
	startBtnText.setPosition(1200, 785);


	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

		}

		window.clear(Color::Black);

		window.draw(backgroundImg);
		window.draw(mainContentImg);
		window.draw(rankingBtn);
		window.draw(rankingBtnText);
		window.draw(startBtn);
		window.draw(startBtnText);

		window.display();
	}
}
