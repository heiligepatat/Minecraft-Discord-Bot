#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "playercount.hpp"
#include "printdebug.hpp"

void trimLineEnding(std::string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

int main(){
    //cooldown between checks in minutes
    int cooldown;
    std::string serverip;
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
            trimLineEnding(line);
            botToken = line;
            debug_print("bottoken: " + botToken);
        }else if (line_nummer == 4){
            trimLineEnding(line);
            channelId = line;
            debug_print("channel id: " + channelId);
        }else if (line_nummer == 6){
            trimLineEnding(line);
            serverip = line;
            debug_print("server ip: " + serverip);
        }else if (line_nummer == 8){
            trimLineEnding(line);
            cooldown = std::stoi(line);
            debug_print("cooldown: " + cooldown);
        }
        line_nummer++;
    }
    bot bot(botToken, channelId, cooldown, serverip);

    while(true){
        std::cout << "Updating logins and logouts" << std::endl;
        debug_print("Tryin to send message");
        bot.pingserver();
        bot.get_online_players();
        bot.update_logins_logouts();
        bot.update_discord();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        debug_print("Message should be sent");
        std::this_thread::sleep_for(std::chrono::minutes(bot.get_cooldown()));
        }
}