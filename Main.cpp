#include "Actions/Actions.hpp"
#include "Menus/Main/MenusMain.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    prepare_data();

    while (window.isOpen())
    {
        if (!sfDATA::MainMenu::ChechMainMenu(window))
        {
            window.close();
            break;
        }
    }

    return 0;
}
