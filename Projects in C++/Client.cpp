#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>

static int g_socket_fd = -1;
static bool g_running = true;

//Continously listens for incoming messages from server and prints them
    void recieve_loop() {
        char buffer[4096];

            while(g_running) {
                ssize_t bytes_read = recv(g_socket_fd, buffer, sizeof(buffer) - 1, 0);

            if(bytes_read <= 0) {
                std::cout <<"\n[Disconnected from server]\n";
                g_running = false;
                break;
            }
            buffer[bytes_read] = '\0';
            std::cout << buffer;
            std::cout.flush();
            }
    }

        //Main block for client.cpp
    int main(int argc, char* argv[]) {
        std::string server_ip = "127.0.0.1";
        int port = 8080;
            if(argc >= 2) 
            server_ip = argv[1];
            if(argc >= 3)
            port = std::atoi(argv[2]);

        g_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            if(g_socket_fd < 0) {
                std::cerr <<"Failed to create socket.\n";
                return 1;
            }

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if(inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {

            std::cerr << "Invalid server address: " << server_ip << "\n";
            return 1;
        }
        if(connect(g_socket_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr) < 0)) {
            std::cerr << "Could not connect to " << server_ip <<":" << port << "\n";

            return 1;
        }

        std::cout <<"Connected to chat server at: " << server_ip <<":" << port << "\n";
        std::cout << "Enter your username: ";
        std::string username;
        std::getline(std::cin, username);
            if(username.empty()) username = "Anonymous";

        std::string init_msg = username + "\n";
        send(g_socket_fd, init_msg.c_str(), init_msg.size(), 0);

        std::cout <<"Type a message and presse enter to send. Type /quit to exit.\n\n";

        std::thread reciever(recieve_loop);
        reciever.detach();

        std::string line;
            while(g_running && std::getline(std::cin, line)) {
                if(line == "/quit") 
                break;
                if(line.empty()) 
                continue;

                line +="\n";
                    if(send(g_socket_fd, line.c_str(), line.size(), 0) < 0) {
                        std::cerr <<"Failed to send message.\n";
                        break;
                    }
            }
            g_running = false;
            close(g_socket_fd);
            std::cout <<"Disconnected.\n";
            return 0;
    }