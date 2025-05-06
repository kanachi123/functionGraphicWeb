#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <fstream>
#include <mutex>
#include <string>
#include <muParser.h>
#include <vector>

using json = nlohmann::json;


int maxThreads = std::thread::hardware_concurrency();
std::mutex mtx;
double h = 0.001;

struct Point {
    double x, y,dx,dy,ddx,ddy;
};

double finite_diff_method(const mu::string_type& exp,double x){
    
    std::vector<Point> points;

    mu::Parser parser;
    parser.SetExpr(exp);
    parser.DefineVar(mu::string_type(L"x"),&x);

    return 0.0;
}

void compute(){

}



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