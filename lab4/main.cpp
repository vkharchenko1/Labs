#include <iostream>
#include "PrintTuple.h"
#include "CSVParser.h"
#include <fstream>

int main() {
    std::ifstream file;
    file.open("test.csv");
    CSVParser<int, std::string, double, double, int, std::string> parser(file, 0);
    for (auto rs : parser)
        std::cout << rs << std::endl;
    file.close();
    return 0;
}