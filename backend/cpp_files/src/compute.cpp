#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <fstream>
#include <mutex>
#include <string>
#include <muParser.h>

using json = nlohmann::json;

int main(){


    std::ifstream inputFile("data.json");
    if(inputFile.is_open() == false){
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    json data;
    inputFile >> data;
    inputFile.close();
    std::cout << "Data loaded successfully" << std::endl;



    
}