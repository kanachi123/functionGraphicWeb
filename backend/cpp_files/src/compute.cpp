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
std::vector<Point> points;

struct Point {
    double x, y,dy_dx,d2y_dx2;
    Point(double x, double y) : x(0), y(0),dy_dx(0.0),d2y_dx2(0.0) {}
};

void compute(const mu::string_type& exp,const json& data,const json& result){
    

    mu::Parser parser;
    parser.SetExpr(exp);

    double x = data["lower"],end = data["upper"] + 1;
    double y {0},i = 0;
    points.reserve(end - x);
    points.resize(end - x);

    while (x < end){
        
        parser.DefineVar(mu::string_type(L"x"),&x);
        points[i].x = x;
        points[i].y = parser.Eval();
        x++;i++;
        finite_diff_method(exp,x,i);
    }

}

void finite_diff_method(const mu::string_type& exp,double x,int i){
    
    mu::Parser parser;
    parser.SetExpr(exp);  
    x +=h;  
    parser.DefineVar(mu::string_type(L"x"),&x);

    points[i].dy_dx = (parser.Eval() - points[i].y) / h;
    
    if(i>0)
    {
        points[i].d2y_dx2 = (points[i].dy_dx - points[i-1].dy_dx) / h;
    }

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

    compute(data["expression"],data,data["result"]);
    std::cout << "Computation completed successfully" << std::endl;
    std::ofstream file("result.json");
    
    file << "{ \"points\": [";

    bool first = true;
    for     (const auto& p : points) {
        if (!first) file << ",";
        file << "{ \"x\": " << p.x << ", \"y\": " << p.y 
             << ", \"dy_dx\": " << p.dy_dx << ", \"d2y_dx2\": " << p.d2y_dx2 << " }";
        first = false;
    }

    file << "] }";
    file.close();
    std::cout << "Result saved successfully" << std::endl;
}