#include <iostream>
#include "PrintTuple.h"
#include "CSVParser.h"
#include <fstream>

int main() {
    std::ifstream file;
    file.open("test.csv");
    CSVParser<int, std::string, double, double, int, std::string> parser(file, 0);
    for (std::tuple<int, std::string, double, double, int, std::string> rs : parser)
        std::cout << rs << std::endl;
    file.close();
    return 0;
}