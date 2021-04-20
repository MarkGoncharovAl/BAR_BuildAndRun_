#include "MainMenus/MainMenus.hpp"

int main()
{
    sf::RenderWindow cur_window(sf::VideoMode::getDesktopMode(), "BAR", sf::Style::Default);
    sfC::Window window{cur_window};
    sfDATA::PrepareData();

    while (window->isOpen())
    {
        if (!sfDATA::MainMenu_t::MainMenu(window))
        {
            window->close();
            break;
        }
    }

    return 0;
}
