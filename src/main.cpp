#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "playercount.hpp"



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
            botToken = line;
        }else if (line_nummer == 4){
            channelId = line;
        }else if (line_nummer == 6){
            serverip = line;
        }else if (line_nummer == 8){
            cooldown = std::stoi(line);
        }
        line_nummer++;
    }
    bot bot(botToken, channelId, cooldown, serverip);

    while(true){
        std::cout << "Tryin to send message" << std::endl;
        bot.pingserver();
        bot.get_online_players();
        bot.update_logins_logouts();
        bot.update_discord();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Message should be sent" << std::endl;
        std::this_thread::sleep_for(std::chrono::minutes(bot.get_cooldown()));
        }
}