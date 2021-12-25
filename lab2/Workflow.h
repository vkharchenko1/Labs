#ifndef LAB2_WORKFLOW_H
#define LAB2_WORKFLOW_H

#include "WF_Block.h"
#include <vector>

class Workflow {
    std::vector<std::pair<int, WF_Block*>> WF_interface;
    std::vector<int> WF_procedure;
public:
    Workflow(std::vector<std::pair<int, WF_Block*>> interface, std::vector<int> procedure);
    ~Workflow();
    void execute();
};


#endif //LAB2_WORKFLOW_H
