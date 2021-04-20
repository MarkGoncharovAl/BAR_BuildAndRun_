#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../Help/Help.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/Text/Text.hpp"
#include "../Common_libs/Errors/Errors.hpp"
#include "../Help/FastDraw.hpp"
#include "../AnalyseMaps/AnalyseText.hpp"

#include <memory>
#include <boost/lexical_cast.hpp>
/*
Network is used for network game:
Starting: Network{}.Start(window)

Returns std::unique_ptr<Network::Socket>() if escaped
*/

namespace sfDATA
{
    class Network final
    {
    private:

        /*
        Base class
        Returns as a pointer to NetworkGame
        Must translate data between client and server
        */
        class Socket
        {
        public:
            Socket () : socket_ (new sf::TcpSocket) {}
            virtual ~Socket () { socket_->disconnect (); delete socket_; }

            virtual bool Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate);
            virtual std::string WhoAmI () { return "socket"; }

        protected:

            /*
            MUST BE STANDART
            pos.x<float> - pos.y<float> - rotate<float>
            return true if connection is still stable
            */
            bool GetPic (sfC::Picture_t& pic);
            bool SendPos (sf::Vector2f const& pos , float rotate);

            //not const because sf:Socket::send(sf::Packet&)
            bool SendPacket (sf::Packet& pack);

            //returns empty packet
            sf::Packet GetPacket ();
            sf::TcpSocket* socket_;
        };

        class ServerSocket final : public Socket
        {
        public:
            ServerSocket (unsigned short port = sf::TcpSocket::AnyPort , sf::IpAddress ip = "127.0.0.1");
            ~ServerSocket () { listener_->close (); delete listener_; }

            void Init ();
            unsigned short GetPort () const noexcept { return listener_->getLocalPort (); }

            bool Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate) override;
            std::string WhoAmI () override { return "Server!"; }

        private:
            sf::TcpListener* listener_;
        };

        class ClientSocket final : public Socket
        {
        public:
            ClientSocket () {}

            //returns true if connection was succesfull
            bool Init (unsigned short port , sf::IpAddress const& ip = "127.0.0.1");
            ~ClientSocket () {}

            std::string WhoAmI () override { return "Client!"; }
            bool Message (sfC::Picture_t& pic , sf::Vector2f const& pos , float rotate) override;
        };

        /////////////////////////////////
           /////////////////////////////////

    public:
        //return false if mistake
        std::unique_ptr<Socket> Start (sfC::Window& window);

    private:

        //Must be only inherenced
        class Data
        {
        public:
            Data () = delete;
            Data (sfC::Window& window);
            Data (const Data&) = delete;
            Data (Data&&) = delete;
            //virtual ~Data () noexcept {} - It can be not declared

        protected:
            sfC::Window& window_;
        };

        class Choose final : public Data
        {
        public:
            enum class Type { Error , Server , Client , Escape , NotChosen };

            Choose (sfC::Window& window);
            Type Start ();

        private:
            Type Analyse ();

            void ServerChoose ();
            void ClientChoose ();
            Type CheckAction ();

            static constexpr bool bool_server_ = true;
            static constexpr bool bool_client_ = false;

            //const, because constexpr isn't allowed
            bool cur_choose_ /*= bool_client*/;
            const sf::IntRect released_ /*= {301 , 377 , 199 , 64}*/;
            const sf::IntRect pressed_ /*= {570 , 377 , 199 , 64}*/;
            sfC::Text_t server_text_;
            sfC::Text_t client_text_;
            sfC::Picture_t server_but_;
            sfC::Picture_t client_but_;

        };

        class Client final : public Data
        {
        public:
            Client (sfC::Window& window);
            std::unique_ptr<Network::Socket> Start ();
        private:
            sfC::Text_t name_;
            sfC::Text_t decl_port_;
            sfC::Text_t num_port_;

            //throw exception if event was unordinary closed
            //return 0 if nothing was chosen
            unsigned short AnalysePort ();
        };

        class Server final : public Data
        {
        public:
            Server (sfC::Window& window);
            std::unique_ptr<Network::Socket> Start ();
        private:
            sfC::Text_t name_;
            sfC::Text_t decl_port_;
            sfC::Text_t num_port_;
        };
    };
}