#include "WF_Parser.h"

int main() {
    try {
        WF_Parser parser("interface.txt");
        Workflow wf = parser.extractInterface();
        wf.execute();
    }
    catch (WF_Exception &exc) {
        std::cout << exc.what() << std::endl;
    }
}