#include <SFML/Graphics.hpp>
#include "WarSide.h"

int main()
{
    srand(time(NULL));
    int shipscount = 5;
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
                    (*i)->choosing_fighters();
            }
            freq_of_movement = 0;
        }
        // tutaj odbywa sie ruch każdego statku co rundę, oraz sprawdzenie czy jakis statek powinien zostać usunięty
        for (auto red = red_team.vships.begin(); red < red_team.vships.end(); red++)
        {
            (*red)->update_position();
            if ((*red)->get_current_life() <= 0)
            {
                for (auto end_fight = vfights.begin(); end_fight < vfights.end(); end_fight++)
                {
                    if ((*end_fight)->get_ship("red") == (*red))
                    {
                        delete* end_fight;
                        vfights.erase(end_fight);
                        break;
                    }
                }
                delete (*red);
                red_team.vships.erase(red);
            }
        }
        for (auto blue = blue_team.vships.begin(); blue < blue_team.vships.end(); blue++)
        {
            (*blue)->update_position();
            if ((*blue)->get_current_life() <= 0)
            {
                for (auto end_fight = vfights.begin(); end_fight < vfights.end(); end_fight++)
                {
                    if ((*end_fight)->get_ship("blue") == (*blue))
                    {
                        delete* end_fight;
                        vfights.erase(end_fight);
                        break;
                    }
                }
                delete (*blue);
                blue_team.vships.erase(blue);
            }
        }
        okno.clear(sf::Color(0, 0, 0));
        // code responsible for displaying every part of ship war like ships, guns, ammo etc.
        for (auto i = blue_team.vships.begin(); i < blue_team.vships.end(); i++)
        {
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle);  // drawing ships
            for (auto b = (*i)->special_magazine.begin(); b < (*i)->special_magazine.end(); b++)
                okno.draw((*b)->draw());  // drawing special attacks
            if ((*i)->is_component_active() == true)
            {
                Component* comp = (*i)->get_component();
                okno.draw(comp->draw());
            }
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
            sf::CircleShape circle = (*i)->draw();
            okno.draw(circle); // drawing ships
            for (auto b = (*i)->special_magazine.begin(); b < (*i)->special_magazine.end(); b++)
                okno.draw((*b)->draw()); // drawing special attacks
            if ((*i)->is_component_active() == true)
            {
                Component* comp = (*i)->get_component();
                okno.draw(comp->draw());
            }
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