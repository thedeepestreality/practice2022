#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

const int PORT = 2024;

int main(int argc, char const* argv[])
{
    // json obj = R"({"files":["source.jpg"]})"_json;
    // std::cout << obj["files"] << '\n';
    // std::cout << obj.dump() << '\n';
    std::string files[] = {"source.jpg", "out.txt"};
    json obj;
    obj["files"] = files;
    auto json_str = obj.dump();
    std::cout << json_str << "\n\n";

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd < 0) {
		perror("Socket creation error");
		exit(EXIT_FAILURE);
	}

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
    // servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "[sender] sender client started\n";

    int status = connect(
        client_fd, 
        (struct sockaddr*)&servaddr,
		sizeof(servaddr)
    );
	if (status < 0) 
    {
        perror("Connection Failed");
		exit(EXIT_FAILURE);
	}

    std::cout << "[sender] sender client connected to server\n";
    char buffer[8];
	int valread = read(client_fd, buffer, 8);
    std::cout << "[sender] server says: [" << buffer << "]\n";
    if (strcmp(buffer,"send") != 0){
        std::cout << "wrong server request\n";
        return 1;
    }
    else{
        send(client_fd, json_str.c_str(), json_str.size(), 0);

        char buffer[50000];
        std::ifstream in("source.jpg",std::ios_base::binary);
        if (!in){
            std::cout << "failed to open file\n";
            return 2;
        }
        in.seekg(0,std::ios_base::end);
        int sz = in.tellg();
        memcpy(buffer, (char*)&sz, 4);
        in.seekg(0, std::ios_base::beg);
        in.clear();
        in.read(buffer+4, sz);
        send(client_fd, buffer, sz + 4, 0);
    }

    std::cout << "[sender] sender sent data\n";

	// closing the connected socket
	close(client_fd);
	return 0;
}
