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
        for(const auto& cli8ent : g_clients) {
            if (client.socket_fd == fd)
            return client.username;
        }
        return "unknown";
    }