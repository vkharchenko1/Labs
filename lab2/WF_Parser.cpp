#include "WF_Parser.h"

WF_Parser::WF_Parser(std::string filename) {
    w_file = filename;
}

Workflow WF_Parser::extractInterface() {
    std::ifstream file;
    file.open(w_file);

    std::string line;

    getline(file, line);
    if (line != "desc")
        throw WF_Exception( "No \"desc\" in the first line\n");

    std::vector<std::pair<int, WF_Block*>> interface(0);

    getline(file, line);
    while (line != "csed") {
        size_t pos = 0;

        if (!isdigit(line[0]))
            throw WF_Exception("Can't initialize a block: no id provided\n");

        int id = stoi(line, &pos, 10);

        std::string argument;

        argument = line.substr(pos, 3);
        if (argument != " = ")
            throw WF_Exception("Can't initialize a block: no assignment operator\n");

        pos+=3;

        std::string type;
        char letter = line[pos];
        while (isdigit(letter) || isalpha(letter)) {
            type += letter;
            pos++;
            letter = line[pos];
        }
        if (type.empty())
            throw WF_Exception("Can't initialize a block: no type provided\n");

        pos++;


        WF_Block* block_ptr;
        if (type == "readfile") {
            block_ptr = new WF_Read(id, &line[pos]);
        }
        else if (type == "writefile") {
            block_ptr = new WF_Write(id, &line[pos]);
        }
        else if (type == "grep") {
            block_ptr = new WF_Grep(id, &line[pos]);
        }
        else if (type == "sort"){
            block_ptr = new WF_Sort(id);
        }
        else if (type == "replace"){
            block_ptr = new WF_Replace(id, &line[pos]);
        }
        else if (type == "dump"){
            block_ptr = new WF_Dump(id, &line[pos]);
        }
        else
            throw WF_Exception("Can't initialize a block: can't recognize a type\n");
        interface.emplace_back(std::pair<int, WF_Block*>{id, block_ptr});

        getline(file, line);
    }

    std::vector<int> procedure(0);
    getline(file, line);
    if (line.empty())
        throw WF_Exception("Can't initialize a procedure: no procedure provided\n");
    size_t pos = 0;

    while (pos != line.length()) {
        std::string value;
        while (isdigit(line[pos])) {
            value += line[pos];
            pos++;
        }
        if (!value.empty())
            procedure.push_back(stoi(value, nullptr, 10));
        else if (line.substr(pos, 4) == " -> ")
            pos+=4;
        else
            throw WF_Exception("Can't initialize a procedure: no following step provided\n");
    }

    file.close();
    return {interface, procedure};
}
