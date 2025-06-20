#include "playercount.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

bot::bot(std::string bottoken, std::string channelid)
    : bottoken_(bottoken), channelid_(channelid)
{
    lastPos_ = 0;
    online_ = std::vector<std::string>(0) ;
    logins_ = std::vector<std::string>(0);
    logouts_ = std::vector<std::string>(0);
    int playercount_ = 0;

    // Check whether valid, might differ from bot to bot
    assert(bottoken_.length() == 72);
    assert(channelid_.length() == 19);
}

static std::string getusername(const std::string& line) {
    size_t end = line.size();
    size_t first_space = end;
    // Find whitespace
    while (first_space > 0 && !(line[first_space - 1] == ' ')) {
        --first_space;
    }
    // Username should be
    std::string username = line.substr(first_space,end);
    return username;
}

void bot::readlog(){
    logins_ = {};
    logouts_ = {};  
    // Start reading file from last position
    std::ifstream file("../latest.log");
    if (!file.is_open()) {
        std::cerr << "Failed to open latest.log\n";
        return;
    } 
    file.seekg(lastPos_);
    std::string word, line;
     while (std::getline(file, line)) {
        size_t size = line.size();
        if (line.substr(size - 22) == " appears in the realm.") {
            logins_.push_back(getusername(line.substr(11,size - 33)));
        }else if (line.substr(size - 18) == " enters the realm."){
            logins_.push_back(getusername(line.substr(11,size - 29)));
        }else if (line.substr(size - 23) == " appears from the Void."){
            logins_.push_back(getusername(line.substr(11,size - 34)));
        }else if (line.substr(size - 30) == " disappears into the darkness."){
            logouts_.push_back(getusername(line.substr(11,size - 41)));
        }
        // Save the new file position for next time
        lastPos_ = file.tellg();
    }
    file.close();
}