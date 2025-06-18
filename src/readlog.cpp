#include <vector>
#include <iostream>
#include <string>
#include <fstream>
void newlogins(std::vector<std::string>& usernames){
    //Check if position.dat
    std::streampos lastPos = 0;
    std::ifstream posIn("../position.dat");
    if (posIn >> lastPos) {
        std::cout << "Resuming from position: " << lastPos << "\n";
    }
    posIn.close();   
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt\n";
        return;
    } 
    file.seekg(lastPos);
        
}