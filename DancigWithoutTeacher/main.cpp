#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "������ ���� ���߱�");

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // â�� ���� �� ����
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}
