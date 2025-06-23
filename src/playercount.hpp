#ifndef PLAYERCOUNT_HPP
#define PLAYERCOUNT_HPP
#include <vector>
#include <string>
#include <fstream>

class bot{

public:
    // create the bot with a valid bottoken and channelid
    bot(std::string bottoken, std::string channelid, int cooldown, std::string serverip);
    // get new and old logins
    void update_logins_logouts();
    void get_online_players();
    void update_discord();
    void pingserver();
    int get_cooldown();

private:
    std::string bottoken_;
    std::string channelid_;
    int cooldown_;
    std::string serverip_;
    std::vector<std::string> previous_online_;
    std::vector<std::string> online_;
    std::vector<std::string> logins_;
    std::vector<std::string> logouts_;
    int playercount_;
    
    
    
} ;
#endif