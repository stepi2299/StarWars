#include <SFML/Graphics.hpp>
#include "WarSide.h"

int main()
{
    srand(time(NULL));
    int shipscount = 5;
    WarSide blue_team = WarSide(shipscount, "blue");
    WarSide red_team = WarSide(shipscount, "red");
    sf::RenderWindow okno(sf::VideoMode(800, 240), "Star Wars", sf::Style::Fullscreen);
    cout << blue_team.vships.size() << endl;
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

        //sf::CircleShape circle = blue_team.vships[1]->draw();
        //okno.draw(circle);
        /*for (auto i = blue_team.vships.begin(); i < blue_team.vships.end(); i++)
        {
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);
        }*/
        //tu obsługa całej gry
        okno.display();
    }
    return 0;
}