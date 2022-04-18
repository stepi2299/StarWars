#include <SFML/Graphics.hpp>
#include "ships.h"
#include "guns.h"
#include "GameTurn.h"

int main()
{
    //sf::RenderWindow okno(sf::VideoMode(800, 240), "Star Wars", sf::Style::Fullscreen);
    srand(time(NULL));
    int i = 20;
    Gun g = BomberGun("bomber", i, 10, 10, 10, 30, 10);
    BomberShip bomber = BomberShip(100, 2, 0.2, 0.3, "bomber", "blue", i, 30, 30, 30, g);

    while (okno.isOpen()) //główna pętla gry
    {
        sf::Event event;
        while (okno.pollEvent(event)) //pętla obsługująca zdarzenia (wynika z architektury biblioteki SFML)
        {
            if (event.type == sf::Event::Closed) //kliknięto przycisk zamknij okno
                okno.close(); //zakończ aplikację

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) //wciśnięto klawisz ESC
                okno.close(); //zakończ aplikację
        }
        okno.clear(sf::Color(0, 0, 0));
        sf::CircleShape circle = bomber.draw();
        okno.draw(circle);
        //tu obsługa całej gry
        okno.display();
    }
    return 0;
}