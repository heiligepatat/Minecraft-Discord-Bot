#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
int parse_file(const std::string filename, std::vector<bool>& booleans, int& update_player_count, int& update_joins) {
    std::ifstream input_file(filename + ".txt");
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }

    std::string line;
    int line_nummer = 1;
    while (std::getline(input_file, line)) {
        
        if (line_nummer < 10 && line_nummer > 3 && line_nummer%2 == 0){
            if (line == "TRUE"){
                booleans[line_nummer/2] = true;
            } else if (line == "FALSE"){
                booleans[line_nummer/2] = false;
            } else{
                std::cout << "Setting on line " << line_nummer << " is invalid, should be either TRUE or FALSE" << std::endl;
                std::cout << "Going further with standard setting " << booleans[line_nummer/2] << std::endl;
            }
        //time between playercount update
        }else if (line_nummer == 10){
            size_t ddot_pos = line.find(':');
            if (ddot_pos != std::string::npos) {
                std::string left = line.substr(0, ddot_pos);
                std::string right = line.substr(ddot_pos + 1);
                int hours, minutes, time;
                hours = 0;
                minutes = 0;
                try {
                    hours = std::stoi(left);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: input is not an integer" << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Hour integer is out of range";
                }
                try {
                    minutes = std::stoi(right);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: input is not an integer" << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Minute integer is out of range";
                }
                time = hours*60 + minutes;
                if (time < 0){
                    std::cout << "Impossible time given of " << time << " total minutes" << std::endl;
                    std::cout << "Routinely player count disabled" << std::endl;
                    update_player_count = 0;

                }else if (time > 2*60*24){
                    std::cout << "Unreasonable time given of " << time << " total minutes, which is more than two days" << std::endl;
                    std::cout << "Routinely player count disabled" << std::endl;
                    update_player_count = 0;
                }else{
                    update_player_count = time;
                }

            } else {
                
                std::cerr << "Wrong format for time, no \":\" found in line " << line_nummer << std::endl;
            }
        }else if (line_nummer == 12){
            int minutes;
            try {
                minutes = std::stoi(line);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: input is not an integer" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Minute integer is out of range";
            }
            if (minutes <= 0){
                std::cout << "Impossible time given of " << time << "total minutes" << std::endl;
                std::cout << "Check for joins each " << update_joins << " minutes instead" << std::endl;

            }else if (minutes > 2*60*24){
                std::cout << "Unreasonable time given of " << time << "total minutes, which is more than two days" << std::endl;
                std::cout << "Check for joins each " << update_joins << " minutes instead" << std::endl;
            }else{
                update_joins = minutes;
            }

            
        }
        line_nummer++;
    }

    input_file.close(); // Close the file
    return 0;
}