//
// Created by v.kharchenko1 on 20.12.2021.
//

#ifndef LAB2_WF_EXCEPTION_H
#define LAB2_WF_EXCEPTION_H

#include <string>

class WF_Exception : std::exception {
    std::string wf_error;
public:
    WF_Exception(std::string error) : wf_error(error) {};
    std::string what() { return wf_error; }
};


#endif //LAB2_WF_EXCEPTION_H
