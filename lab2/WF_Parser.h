#ifndef LAB2_WF_PARSER_H
#define LAB2_WF_PARSER_H

#include "Workflow.h"
#include <vector>

class WF_Parser {
    std::string w_file;
public:
    explicit WF_Parser(std::string filename);
    Workflow extractInterface();
};


#endif //LAB2_WF_PARSER_H
