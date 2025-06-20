#include <vector>
#include <iostream>
#include <string>
#include <fstream>

std::string getusername(const std::string& line) {
    size_t end = line.size();
    size_t first_space = end;
    // Trim trailing whitespace
    while (first_space > 0 && !(line[first_space - 1] == ' ')) {
        --first_space;
    }
    //username should be
    std::string username = line.substr(first_space,end);
    return username;
}




void playerlogins_logouts(std::vector<std::string>& logins, std::vector<std::string>& logouts){
    //Check if position.dat
    std::streampos lastPos = 0;
    std::ifstream posIn("../position.dat");
    long long tmp;
    if (posIn >> tmp) {
            lastPos = static_cast<std::streampos>(tmp);
        }
    posIn.close();   
    //Start reading file from last position
    std::ifstream file("../latest.log");
    if (!file.is_open()) {
        std::cerr << "Failed to open latest.log\n";
        return;
    } 
    file.seekg(lastPos);
    std::string word, line;
    std::streampos lastValidPos = file.tellg();
     while (std::getline(file, line)) {
        size_t size = line.size();
        if (line.substr(size - 22) == " appears in the realm.") {
            logins.push_back(getusername(line.substr(11,size - 33)));
        }else if (line.substr(size - 18) == " enters the realm."){
            logins.push_back(getusername(line.substr(11,size - 29)));
        }else if (line.substr(size - 23) == " appears from the Void."){
            logins.push_back(getusername(line.substr(11,size - 34)));
        }else if (line.substr(size - 30) == " disappears into the darkness."){
            logouts.push_back(getusername(line.substr(11,size - 41)));
        }
        lastValidPos = file.tellg();
    }
    std::ofstream posOut("position.dat");
    posOut << lastValidPos;  // Save current read position
    posOut.close();
    
    for (size_t i = 0; i < logins.size(); i++){
        std::cout << logins[i] << std::endl;
    }
    
    // Save the new file position for next time
    
    file.close();
}
int main(){
    std::cout << std::endl << "readlog started" << std::endl;
    std::ofstream posOut("position.dat");
    posOut << 0;
    posOut.close();

    std::vector<std::string> usernames;
    playerlogins_logouts(usernames, usernames);
}