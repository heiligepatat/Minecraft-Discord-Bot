#include "playercount.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "discordmessage.hpp"
bot::bot(std::string bottoken, std::string channelid, int cooldown, std::string serverip)
    : bottoken_(bottoken), channelid_(channelid), cooldown_(cooldown), serverip_(serverip)
{
    previous_online_ = std::vector<std::string>(0);
    online_ = std::vector<std::string>(0);
    logins_ = std::vector<std::string>(0);
    logouts_ = std::vector<std::string>(0);
    int playercount_ = 0;

    // Check whether valid, might differ from bot to bot
    assert(bottoken_.length() == 72);
    assert(channelid_.length() == 19);
}


void bot::update_discord(){
    std::string message;
    for (int i = 0; i < logins_.size(); ++i){
        message = logins_[i] + " joined the server";
        std::cout << message << std::endl;
        sendDiscordMessage(bottoken_, channelid_, message);
    }
    for (int i = 0; i < logouts_.size(); ++i){
        message = logouts_[i] + " left the server";
        std::cout << message << std::endl;
        sendDiscordMessage(bottoken_, channelid_, message);
    }
}

void bot::get_online_players() {
    std::ifstream file("../server_info.txt");
    if (!file) {
        std::cerr << "Failed to open file.\n";
        return;
    }
    std::string content;
    std::cout << std::endl;
    online_ =  {};
    playercount_ = 0;
    std::getline(file, content);  
    file.close();
    std::string playercount = "";
    for (size_t i = 0; i < content.length(); ++i) {
        /* search JSON (.txt format) for keys
                                        "players":{"online":
        after which comes the online playercount
        */ 
        if (',' == content[i] && ("\"players\":{\"online\":" == content.substr(i+1, 20 ))) {
            i = i + 21;
            // store the playercount number to crossreference size of the username list that will be created
            while (content[i] != ',' && i < content.length()){  
                playercount = playercount + content[i];
                i++;
            }
            playercount_ = std::stoi(playercount);
            // search for the "list" key which stores the usernames
            while ("\"list\":[" != content.substr(i, 8) && i < content.length()){
                i++;
            }
            i = i+8;
            // find the "name_clean" key and get the associated username value
            while (online_.size() != playercount_ && content[i] != ']'){
                while (",\"name_clean\":\"" != content.substr(i, 15) && content[i] != ']'){
                    i++;
                }
                if (content[i] != ']'){
                    i = i + 15;
                }
                std::string temp_username = "";
                while (content[i] != '\"' && content[i] != ']'){
                    temp_username = temp_username + content[i];   
                    i++;                     
                }
                online_.push_back(temp_username);
                while (content[i] != '}' && content[i] != ']'){
                    i++;
                }
                if (content[i] != ']'){
                    i++;
                }
            }  
            return;         
        }
    }
    return;
}
void bot::update_logins_logouts(){
    logins_ = {};
    logouts_ = {};
    for (int i = 0; i < online_.size(); ++i){
        std::cout << online_[i] << std::endl;
    }
    for (int i = 0; i < previous_online_.size(); ++i){
        std::cout << previous_online_[i] << std::endl;
    }

    for (int i = 0; i < online_.size(); ++i){
        bool logged_in = true;
        for (int j = 0; j < previous_online_.size(); ++j){
            if (online_[i] == previous_online_[j]){
                logged_in = false;
            }        
        }
        if (logged_in){
            logins_.push_back(online_[i]);
        }
    }

    for (int i = 0; i < previous_online_.size(); ++i){
        bool logged_out = true;
        for (int j = 0; j < online_.size(); ++j){
            if (online_[j] == previous_online_[i]){
                logged_out = false;
            }        
        }
        if (logged_out){
            logouts_.push_back(previous_online_[i]);
        }
    }
    previous_online_ = {};
    previous_online_ = online_;
}
void bot::pingserver(){
    std::string command = "curl https://api.mcstatus.io/v2/status/java/" + serverip_ + " > ../server_info.txt"; 
    int ret = system(command.c_str());
    if (ret != 0) {
        std::cerr << "curl command failed with exit code " << ret << std::endl;
    }
}