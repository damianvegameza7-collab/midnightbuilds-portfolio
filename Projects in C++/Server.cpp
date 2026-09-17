#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

struct Client {
    int socket_fd;
    std::string username;
};

static std::vector<Client> g_clients;
static std::mutex g_clients_mutex;

//Sends a message to every connected client except one to skip
    void broadcast (const std::string& message, int skip_fd = -1){
        std::lock_guard<std::mutex> lock(g_clients_mutex);
        for(const auto& client : g_clients) {
            if(client.socket_fd == skip_fd) continue;
            send(client.socket_fd, message.c_str(), message.size(), 0);

    }
}

    void remove_client(int fd) {
        std::lock_guard<std::mutex> lock(g_clients_mutex);
        g_clients.erase(
            std::remove_if(g_clients.begin(), g_clients.end(), 
        [fd](const Client& c) { return c.socket_fd == fd;
        }),
            g_clients.end());
    }

    std::string get_username(int fd) {
        std::lock_guard<std::mutex> lock(g_clients_mutex);
        for(const auto& client : g_clients) {
            if (client.socket_fd == fd) 
            return client.username;
        }
        return "unknown";
    }
    void handle_client(int client_fd) {
        char buffer[4096];

    //First message from the client is treated as their chosen username
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if(bytes_read <= 0) {
            close(client_fd);
            return;
        }
        buffer[bytes_read] = '\0';
        std::string username(buffer);
    //Strip trailing newline/carriage return, if any
        while(!username.empty() && (username.back() == '\n' || username.back()
    == '\r')) {
        username.pop_back();
    }
        if(username.empty()) username = "Anonymous"; {
            std::lock_guard<std::mutex> lock(g_clients_mutex);
            g_clients.push_back({client_fd, username});
        }
        std::cout <<"[+] " << username <<"joined \n";
        broadcast("*** " + username + " has joined the chat **\n", client_fd);

    //Main reciever loop
        while(true) {
            bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
                if(bytes_read <= 0) 
            //Disconnected or error
                break;
            buffer[bytes_read] = '\0';

            std::string msg(buffer);
                while(!msg.empty() && (msg.back() == '\n' || msg.back() == '\r')) {
                    msg.pop_back();
                }
            if(msg.empty()) continue;
            std::cout << username <<": " <<msg <<"\n";
            broadcast(username +": " + msg + "\n", client_fd);
        }
        remove_client(client_fd);
        close(client_fd);
        std::cout <<"[-] " << username <<" left.\n";
        broadcast("*** " + username + " has left the chat ***\n");
    }

        //Main block for server.cpp
        int main(int argc, char* argv[]) {
        int port = 8080;
            if(argc >= 2) port = std::atoi(argv[1]);

        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
            if(server_fd < 0) {
                std::cerr <<"Failed to create socket.\n";
                return 1;
            }
        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
        sizeof(opt));

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

            if(bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address))
        < 0) {
            std::cerr <<"Bind failed on port " << port <<".\n";
            close(server_fd);
            return 1;
        }
            if(listen(server_fd, 16) < 0) {
                std::cerr <<"Listen failed.\n";
                close(server_fd);
                return 1;
            }
            std::cout <<"Chat server listening on port " << port <<".\n";

                while(true) {
                    sockaddr_in client_addr{};
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr),
                &client_len);
                    if(client_fd < 0) {
                        std::cerr <<"Accept failed.\n";
                        continue;
                    }
                    std::thread(handle_client, client_fd).detach();
                }
                close(server_fd);
                return 0;
    }