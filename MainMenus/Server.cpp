#include "Server.hpp"

//WRITE DRAW FUNCTION

namespace sfDATA
{
    Network::Data::Data (sfC::Window& window)
        : window_ (window)
    {}
    Network::Choose::Choose (sfC::Window& window)
        : Data (window) ,
        cur_choose_ (bool_client_) ,
        released_ (301 , 377 , 199 , 64) ,
        pressed_ (570 , 377 , 199 , 64) ,
        server_text_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (370 , 515) , "Server") ,
        client_text_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (1095 , 520) , "Client") ,
        server_but_ ("../Images/buttons2.png" , sf::IntRect (301 , 377 , 199 , 64) , sf::Vector2f (300.f , 500.f) , sf::Color (255 , 255 , 255) , sf::Vector2f (2.f , 2.f)) ,
        client_but_ ("../Images/buttons2.png" , sf::IntRect (570 , 377 , 199 , 64) , sf::Vector2f (1000.f , 500.f) , sf::Color (255 , 255 , 255) , sf::Vector2f (2.f , 2.f))
    {
        server_text_.set_color (sf::Color::Black);
        client_text_.set_color (sf::Color::Black);
    }
    Network::Server::Server (sfC::Window& window)
        : Data (window) ,
        name_ (sfCON_FILE_Fonts_ttf , 80 , sf::Vector2f (300 , 100) , "SERVER") ,
        decl_port_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (300 , 400) , "Port:") ,
        num_port_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (520 , 400) , "")
    {
        name_.set_color (sf::Color::Magenta);
        decl_port_.set_color (sf::Color::Magenta);
        num_port_.set_color (sf::Color::Magenta);
    }
    Network::Client::Client (sfC::Window& window)
        : Data (window) ,
        name_ (sfCON_FILE_Fonts_ttf , 80 , sf::Vector2f (300 , 100) , "CLIENT") ,
        decl_port_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (300 , 400) , "Port:") ,
        num_port_ (sfCON_FILE_Fonts_ttf , 70 , sf::Vector2f (520 , 400) , "")
    {
        name_.set_color (sf::Color::Magenta);
        decl_port_.set_color (sf::Color::Magenta);
        num_port_.set_color (sf::Color::Magenta);
    }

    std::unique_ptr<Network::Socket> Network::Start (sfC::Window& window)
    {
        switch (Choose { window }.Start ())
        {
        case Choose::Type::Client:
            return Client { window }.Start ();
        case Choose::Type::Server:
            return Server { window }.Start ();
        case Choose::Type::Escape:
            return std::unique_ptr<Network::Socket> ();

        default:
            break;
        };

        LOG_error << "Can't find declaration for Type!"; //next case too
        throw std::runtime_error ("Can't find declaration for Type!");
        return std::unique_ptr<Network::Socket> ();
    }

    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
    Network::Choose::Type
        Network::Choose::Start ()
    {
        sfF::SetDefaultView (window_);

        while (window_->isOpen ())
        {
            window_.Draw (sfCON::Saving2PNG , server_but_ , client_but_ , server_text_ , client_text_);

            auto&& ret = Analyse ();
            if (ret != Type::NotChosen)
                return ret;
        }

        return Type::Error; //window is closed unexpectably
    }

    Network::Choose::Type
        Network::Choose::Analyse ()
    {
        sf::Event event;

        while (window_->pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
            {
                LOG_warning << "Window are closed, but not predicted!";
                return Type::Error;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    return Type::Escape;
                case sf::Keyboard::Right: //!MUST BE REPLACED
                    ClientChoose ();
                    break;
                case sf::Keyboard::Left: //!MUST BE REPLACED
                    ServerChoose ();
                    break;
                case sf::Keyboard::Enter:
                    return CheckAction ();
                default:
                    break; //waiting for interesting action
                }
            }
        }

        return Type::NotChosen;
    }

    void Network::Choose::ClientChoose ()
    {
        cur_choose_ = bool_client_;
        server_but_.set_texture (released_);
        client_but_.set_texture (pressed_);
    }
    void Network::Choose::ServerChoose ()
    {
        cur_choose_ = bool_server_;
        server_but_.set_texture (pressed_);
        client_but_.set_texture (released_);
    }
    Network::Choose::Type Network::Choose::CheckAction ()
    {
        //to default options
        server_but_.set_texture (released_);
        client_but_.set_texture (pressed_);

        if (cur_choose_)
            return Type::Server;
        return Type::Client; //else
    }

    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////

    std::unique_ptr<Network::Socket> Network::Server::Start ()
    {
        auto server = std::make_unique<ServerSocket> ();

        auto&& port = server->GetPort ();
        num_port_.set_text (std::to_string (port));

        window_.Draw (sfCON::Saving2PNG , name_ , decl_port_ , num_port_);

        server->Init ();
        std::cout << "Connected!\n";

        auto out = std::make_unique<Socket> ();
        out = std::move (server);
        return out;
    }

    std::unique_ptr<Network::Socket> Network::Client::Start ()
    {
        auto&& client = std::make_unique<ClientSocket> ();
        unsigned short port = 0;

        while (true)
        {
            try
            {
                port = AnalysePort ();
                if (client->Init (port)) //success
                    break;
            }
            catch (boost::exception& err)
            {
                name_.set_text ("Can't connect. Enter again");
                num_port_.set_text ("");
            }
        }
        std::cout << "Connected!\n";

        auto out = std::make_unique<Socket> ();
        out = std::move (client);
        return out;
    }

    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////

    unsigned short Network::Client::AnalysePort ()
    {
        while (window_->isOpen ())
        {
            sf::Event event;
            while (window_->pollEvent (event))
            {
                if (event.type == sf::Event::Closed)
                {
                    LOG_warning << "Window are closed, but not predicted!";
                    throw std::runtime_error { "Can't define port" };
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        return 0;
                    case sf::Keyboard::Enter:
                        return boost::lexical_cast<unsigned short>(num_port_.get_text ());
                    case sf::Keyboard::BackSpace:
                        num_port_.pop_back ();
                        break;
                    default:
                        break;
                    }
                }

                if (event.type == sf::Event::TextEntered
                        && event.text.unicode >= '0'
                        && event.text.unicode <= '9')
                {
                    char cur_symbol = static_cast<char>(event.text.unicode);
                    num_port_.push_back (cur_symbol);
                }
            }

            window_.Draw (sfCON::Saving2PNG , name_ , decl_port_ , num_port_);
        }
        return 0;
    }

    ///////////////////////////////////
    ///////////////////////////////////

    sf::Packet Network::Socket::GetPacket ()
    {
        sf::Packet packet;
        if (socket_->receive (packet) != sf::Socket::Done)
            LOG_debug << "Can't get info from socket";
        return packet;
    }

    bool Network::Socket::Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate)
    {
        LOG_fatal << "Can't expected!" << pic.get_loc_bounds().left << pos.x << rotate;
        throw std::runtime_error("Can't expect!");
        return false;
    }

    bool Network::Socket::GetPic (sfC::Picture_t& pic)
    {
        auto&& pack = GetPacket();
        if (pack.endOfPacket())
            return false;

        float x = 0, y = 0, rotate = 0;
        pack >> x >> y >> rotate;
        if (!pack || !pack.endOfPacket())
        {
            LOG_debug << "Conncecion was lost";
            return false;
        }
        pic.set_position(x, y);
        pic.set_rotation(rotate);
        return true;
    }
    bool Network::Socket::SendPos (sf::Vector2f const& pos , float rotate)
    {
        sf::Packet out;
        out << pos.x << pos.y << rotate;
        return SendPacket(out);
    }

    bool Network::ServerSocket::Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate)
    {
        return GetPic (pic) && SendPos (pos , rotate);
    }
    bool Network::ClientSocket::Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate)
    {
        return SendPos (pos , rotate) && GetPic (pic);
    }

    bool Network::Socket::SendPacket (sf::Packet& pack)
    {
        if (socket_->send (pack) != sf::Socket::Done)
        {
            LOG_debug << "Can't send packet " << pack << " to socket";
            return false;
        }
        return true;
    }

    Network::ServerSocket::ServerSocket (unsigned short port /*= sf::TcpSocket::AnyPort*/ , sf::IpAddress ip/* = "127.0.0.1"*/)
    {
        listener_ = new sf::TcpListener;
        if (listener_->listen (port , ip) != sf::Socket::Done)
        {
            LOG_fatal << "Can't listen to socket. IP: " << ip << " Port: " << port;
            throw std::runtime_error ("Can't listen to socket!");
        }
    }

    void Network::ServerSocket::Init ()
    {
        if (listener_->accept (*socket_) != sf::Socket::Done)
        {
            LOG_fatal << "Can't accept client!";
            throw std::runtime_error ("Can't accept client!");
        }
    }

    bool Network::ClientSocket::Init (unsigned short port , sf::IpAddress const& ip /* = "127.0.0.1"*/)
    {
        if (socket_->connect (ip , port) != sf::Socket::Done)
        {
            LOG_warning << "Can't connect to socket. IP: " << ip << " Port: " << port;
            return false;
        }
        return true;
    }
}
