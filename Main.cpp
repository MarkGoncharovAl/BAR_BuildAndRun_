#include "ALL/ALL.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    sfDATA::PrepareData();

    while (window.isOpen())
    {
        if (!sfDATA::MainMenu_t::MainMenu(window))
        {
            window.close();
            break;
        }
    }

    return 0;
}
