#include <SFML/Graphics.hpp>
#include "WarSide.h"

int main()
{
    srand(time(NULL));
    int shipscount = 8;
    sf::RenderWindow okno(sf::VideoMode(800, 240), "Star Wars", sf::Style::Fullscreen);
    sf::Vector2i window_dims(okno.getSize().x, okno.getSize().y);
    WarSide blue_team = WarSide(shipscount, "blue", window_dims);
    WarSide red_team = WarSide(shipscount, "red", window_dims);
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
        for (auto i = blue_team.vships.begin(); i < blue_team.vships.end(); i++)
        {
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);
            for (auto j = (*i)->armory.begin(); j < (*i)->armory.end(); j++)
            {
                sf::RectangleShape rec = (*j)->draw();
                okno.draw(rec);
            }
        }
        for (auto i = red_team.vships.begin(); i < red_team.vships.end(); i++)
        {

            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);
            for (auto j = (*i)->armory.begin(); j < (*i)->armory.end(); j++)
            {
                sf::RectangleShape rec = (*j)->draw();
                okno.draw(rec);
            }
        }

        //tu obsługa całej gry
        okno.display();
    }
    return 0;
}