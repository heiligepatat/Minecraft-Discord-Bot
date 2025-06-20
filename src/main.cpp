#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <fstream>
#include "playercount.hpp"


// Escape string for Windows cmd.exe (double quotes + backslashes)
std::string PreventEscapeFromCmd(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c == '\\') result += "\\\\";
        else if (c == '"') result += "\\\"";
        else result += c;
    }
    return result;
}


// Send a Discord message to a channel using curl
void sendDiscordMessage(const std::string& token, const std::string& channelId, const std::string& message) {
    // Build JSON payload
    std::string payload = "{\"content\": \""; 

    for (char c : message) {
        if (c == '\\') payload += "\\\\";
        else if (c == '"') payload += "\\\"";
        else payload += c;
    }

    payload += "\"}";
    std::string NewPayload = PreventEscapeFromCmd(payload);

#ifdef _WIN32
    // Command for windows
        std::string command = "curl -s -X POST https://discord.com/api/v10/channels/" + channelId +
                          "/messages -H \"Authorization: Bot " + token +
                          "\" -H \"Content-Type: application/json\" -d \"" + NewPayload + "\"";
#else
    // On Linux, wrap payload in single quotes instead of double quotes
    std::string command = "curl -s -X POST https://discord.com/api/v10/channels/" + channelId +
                          "/messages -H \"Authorization: Bot " + token +
                          "\" -H \"Content-Type: application/json\" -d '" + NewPayload + "'";
#endif
    // NOT TESTED ON LINUX, FORMAT OF "command" SHOULD BE RIGHT
    int ret = system(command.c_str());
    if (ret != 0) {
        std::cerr << "curl command failed with exit code " << ret << std::endl;
    }
}



int main(){
    std::cout << std::endl << "Discord bot started" << std::endl;

    //read bot token and channel id
    std::ifstream input_file("../bot.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }
    std::string line, botToken, channelId;
    int line_nummer = 1;
    while (std::getline(input_file, line)) {
        if (line_nummer == 2){
            botToken = line;
        }else if (line_nummer == 4){
            channelId = line;
        }
        line_nummer++;
    }
    bot bot(botToken, channelId);
    

    // Set read possition to 0 on startup
    std::ofstream posOut("../position.dat");
    posOut << 0;  
    posOut.close();

    while(true){
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Tryin to send message" << std::endl;
        sendDiscordMessage(botToken, channelId, input);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Message should be sent" << std::endl;
        }
}