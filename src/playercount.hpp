#ifndef PLAYERCOUNT_HPP
#define PLAYERCOUNT_HPP
#include <vector>
#include <string>
#include <fstream>

class bot{

public:
    // create the bot with a valid bottoken and channelid
    bot(std::string bottoken, std::string channelid);
    // get new and old logins
    void bot::readlog();


private:
    std::vector<std::string> online_;
    std::vector<std::string> logins_;
    std::vector<std::string> logouts_;
    int playercount_;
    std::string bottoken_;
    std::string channelid_;
    std::streampos lastPos_;
    
} ;
#endif