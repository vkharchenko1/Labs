#include "Workflow.h"

#include <utility>

Workflow::Workflow(std::vector<std::pair<int, WF_Block *>> interface, std::vector<int> procedure) {
    WF_interface = std::move(interface);
    WF_procedure = std::move(procedure);
}


Workflow::~Workflow() {
    WF_interface.clear();
    WF_procedure.clear();
}

void Workflow::execute() {
    std::string* text = nullptr;

    for (auto step : WF_procedure) {
        std::pair<int, WF_Block*> cur_block;
        cur_block = *std::find_if(WF_interface.begin(), WF_interface.end(), [&](std::pair<int, WF_Block*> const & ref) {
            return ref.first == step;
        });
        text = cur_block.second->doBlock(text);
    }
}
