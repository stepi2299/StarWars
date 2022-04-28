#include <SFML/Graphics.hpp>
#include "WarSide.h"

int main()
{
    srand(time(NULL));
    int shipscount = 7;
    int freq_of_movement = 0;
    sf::RenderWindow okno(sf::VideoMode(800, 240), "Star Wars", sf::Style::Fullscreen);
    sf::Vector2i window_dims(okno.getSize().x, okno.getSize().y);
    WarSide blue_team = WarSide(shipscount, "blue", window_dims);
    WarSide red_team = WarSide(shipscount, "red", window_dims);
    vector <Fight*> vfights;
    while (okno.isOpen()) //główna pętla gry
    {
        sf::Event event;
        vector <Fight*> tmp_fights;
        while (okno.pollEvent(event)) //pętla obsługująca zdarzenia (wynika z architektury biblioteki SFML)
        {
            if (event.type == sf::Event::Closed) //kliknięto przycisk zamknij okno
                okno.close(); //zakończ aplikację

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) //wciśnięto klawisz ESC
                okno.close(); //zakończ aplikację
        }
        tmp_fights = red_team.find_opponents(blue_team);
        for (auto i = tmp_fights.begin(); i < tmp_fights.end(); i++)
            vfights.push_back((*i));
        if (freq_of_movement >= 50)
        {
            for (auto i = vfights.begin(); i < vfights.end(); i++)
            {
                (*i)->move_all_ammo();
                if ((*i)->get_on_place() == 0)
                    (*i)->move_to_fighting_position();
                else
                {
                    if ((*i)->choosing_fighters() == true)
                    {
                        cout << "trt" << endl;
                        vfights.erase(i);
                    }
                }
            }
            freq_of_movement = 0;
        }
        okno.clear(sf::Color(0, 0, 0));
        for (auto i = blue_team.vships.begin(); i < blue_team.vships.end(); i++)
        {
            if ((*i)->get_current_life() <= 0)
            {
                cout << "sdds" << endl;
                blue_team.vships.erase(i);
                delete (*i);
            }
            (*i)->update_position();
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);
            for (auto j = (*i)->armory.begin(); j < (*i)->armory.end(); j++)
            {
                sf::RectangleShape rec = (*j)->draw();
                okno.draw(rec);
                for (auto ij = (*j)->magazine.begin(); ij < (*j)->magazine.end(); ij++)
                {
                    sf::RectangleShape rec = (*ij)->draw();
                    okno.draw(rec);
                }
            }

        }
        for (auto i = red_team.vships.begin(); i < red_team.vships.end(); i++)
        {
            if((*i)->get_current_life() <= 0)
            {
                red_team.vships.erase(i);
                delete (*i);
            }
            (*i)->update_position();
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);
            for (auto j = (*i)->armory.begin(); j < (*i)->armory.end(); j++)
            {
                sf::RectangleShape rec = (*j)->draw();
                okno.draw(rec);
                for (auto ij = (*j)->magazine.begin(); ij < (*j)->magazine.end(); ij++)
                {
                    sf::RectangleShape rec = (*ij)->draw();
                    okno.draw(rec);
                }
            }
        }
        okno.display();
        freq_of_movement++;
    }
    return 0;
}