#include "CreateMap.hpp"

#include "../Help/Help.hpp"
#include "AnalyseText.hpp"
#include "MapPrototypes.hpp"
#include "SetMap.hpp"
#include "../MainMenus/MainMenus.hpp"

sfC::Map sfDATA::CreateMap_t::map ("../Images/blocks3.png");
sfC::Picture_t sfDATA::CreateMap_t::info_user ("../Images/To_create_menu.png" , sf::IntRect (243 , 277 , 180 , 265) , sf::Vector2f (10.f , 812.f) , sf::Color::Magenta);

sf::View sfDATA::CreateMap_t::view (sf::FloatRect (0.f , 0.f , sfCON::WindowWidth , sfCON::WindowHeight));

std::map<sfDATA::CreateMap_t::data_for_keys , bool> sfDATA::CreateMap_t::keys;

std::stack<sfDATA::CreateMap_t::data_for_stack> sfDATA::CreateMap_t::actions;

sfC::BlockPrototype::TypeBlock sfDATA::CreateMap_t::cur_block = sfC::BlockPrototype::TypeBlock::Wall;

void sfDATA::CreateMap_t::update_mouse (int x , int y) noexcept
{
    if (x < sfCON::WindowWidth * 0.1f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left] = false;
    if (x > sfCON::WindowWidth * 0.85f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] = false;
    if (y < sfCON::WindowHeight * 0.15f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up] = false;
    if (y > sfCON::WindowHeight * 0.80f)
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] = true;
    else
        sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] = false;
}
void sfDATA::CreateMap_t::update_block (const sf::Vector2i& block , sfC::BlockPrototype::TypeBlock type) noexcept
{
    sfC::BlockPrototype::TypeBlock old_type = sfDATA::CreateMap_t::map.get_type_block (block);

    if (sfDATA::CreateMap_t::map.change_block (block , type))
    {

        if (sfDATA::CreateMap_t::actions.empty ())
        {
            sfDATA::CreateMap_t::actions.push (sfDATA::CreateMap_t::data_for_stack (block , old_type));
            return;
        }
        if (!sfDATA::CreateMap_t::actions.top ().is_equal (block , type))
            sfDATA::CreateMap_t::actions.push (sfDATA::CreateMap_t::data_for_stack (block , old_type));
    }
}
void sfDATA::CreateMap_t::cancel_last_update () noexcept
{
    if (!sfDATA::CreateMap_t::actions.empty ())
    {
        sfDATA::CreateMap_t::data_for_stack prev_block = sfDATA::CreateMap_t::actions.top ();
        sfDATA::CreateMap_t::actions.pop ();

        sfDATA::CreateMap_t::map.change_block (prev_block.block , prev_block.type);
    }
}
void sfDATA::CreateMap_t::move_view () noexcept
{
    sfDATA::CreateMap_t::view.move (
        sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Right] - sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Left] ,
        sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Down] - sfCON::SPEED_CAMERA * sfDATA::CreateMap_t::keys[sfDATA::CreateMap_t::data_for_keys::Mouse_Up]);
}
void sfDATA::CreateMap_t::clear_stack () noexcept
{
    while (!sfDATA::CreateMap_t::actions.empty ())
        sfDATA::CreateMap_t::actions.pop ();
}

void sfDATA::CreateMap_t::PrepareData ()
{
    MainGame_t::PrepareData (sfDATA::CreateMap_t::map);

    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Button_Left , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Ctrl , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Z , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Mouse_Down , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Mouse_Up , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Mouse_Right , false));
    sfDATA::CreateMap_t::keys.insert (std::make_pair (sfDATA::CreateMap_t::data_for_keys::Mouse_Left , false));
}
//++++++++++++++++++++++++++++++++++++++

// !sfDATA::Text_t
//((((((((((((((((((((((((((((((((((((((

bool sfDATA::CreateMap_t::AnalyseCreateMap (sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::Closed)
            return false;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2f coords (event.mouseButton.x + sfF::get_view_position_x (view) ,
                                    event.mouseButton.y + sfF::get_view_position_y (view));

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < map.GetSize ().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < map.GetSize ().y - sfCON::SIZE_BLOCK))
                {
                    update_block (
                        map.AbsCoords (coords) , cur_block);
                }

                keys[data_for_keys::Button_Left] = true;
            }
        }
        if (event.type == sf::Event::MouseMoved)
        {
            if (keys[data_for_keys::Button_Left])
            {

                sf::Vector2f coords (event.mouseMove.x + sfF::get_view_position_x (view) ,
                                    event.mouseMove.y + sfF::get_view_position_y (view));

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < map.GetSize ().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < map.GetSize ().y - sfCON::SIZE_BLOCK))
                {
                    update_block (
                        map.AbsCoords (coords) , cur_block);
                }
            }

            update_mouse (event.mouseMove.x , event.mouseMove.y);
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                keys[data_for_keys::Button_Left] = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                keys[data_for_keys::Ctrl] = true;
                break;
            case sf::Keyboard::Z:
                keys[data_for_keys::Z] = true;
                if (keys[data_for_keys::Ctrl] == true)
                    cancel_last_update ();
                break;
            case sf::Keyboard::S:
                keys[data_for_keys::S] = true;
                if (keys[data_for_keys::Ctrl] == true)
                {
                    std::string new_name = sfDATA::Text_t::WaitTextUser (window);

                    if (!new_name.empty ())
                    {
                        sfDATA::Text_t::ShowDoneAction (window , new_name , "created");
                        sfDATA::MapPrototypes_t::insert_map (new_name , map.get_map_prototype ());
                    }
                    else
                    {
                        sfDATA::Text_t::ShowDoneAction (window , "Not created!");
                    }
                }
                break;
            case sf::Keyboard::Num1:
                cur_block = sfC::BlockPrototype::TypeBlock::Field;
                break;
            case sf::Keyboard::Num2:
                cur_block = sfC::BlockPrototype::TypeBlock::Wall;
                break;
            case sf::Keyboard::Num3:
                cur_block = sfC::BlockPrototype::TypeBlock::Target;
                break;
            case sf::Keyboard::Num4:
                cur_block = sfC::BlockPrototype::TypeBlock::Sand;
                break;
            case sf::Keyboard::Num5:
                cur_block = sfC::BlockPrototype::TypeBlock::Acceleration;
                break;
            case sf::Keyboard::Num6:
                cur_block = sfC::BlockPrototype::TypeBlock::Restart;
                break;
            case sf::Keyboard::Escape:
                sfDATA::Text_t::ShowDoneAction (window , "Not created");
                return false;
                break;
            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                keys[data_for_keys::Ctrl] = false;
                break;
            case sf::Keyboard::Z:
                keys[data_for_keys::Z] = false;
                break;
            case sf::Keyboard::S:
                keys[data_for_keys::S] = false;
                break;
            default:
                break;
            }
        }
    }

    move_view ();
    return true;
}

bool sfDATA::CreateMap_t::CreateMap (sf::RenderWindow& window)
{
    sfDATA::SetMap_t::PrepareCreateMap (window , map);

    while (window.isOpen ())
    {
        if (!AnalyseCreateMap (window))
            break;

        window.clear ();

        window.setView (view);
        window.draw (map);

        info_user.set_position (
            sfF::get_view_position_x (view) ,
            765.f + sfF::get_view_position_y (view));
        window.draw (info_user.for_draw ());
        window.display ();
    }

    return false;
}