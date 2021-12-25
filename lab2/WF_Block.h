#ifndef LAB2_WF_BLOCK_H
#define LAB2_WF_BLOCK_H

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "WF_Exception.h"

enum Block {
    NONE = 0,
    READ = 1,
    WRITE = 2,
    GREP = 3,
    SORT = 4,
    REPLACE = 5,
    DUMP = 6
};

//Parent Block
class WF_Block {
protected:
    int w_num;
    Block w_type;

    WF_Block();

public:
    int getNumber() const;
    int getType() const;
    virtual std::string* doBlock(std::string* in_text) = 0;
};

//Reading Block
class WF_Read: public WF_Block{
    std::string w_file;
public:
    WF_Read(int num, const std::string& filename);
    std::string* doBlock(std::string* in_text);
};

//Writing Block
class WF_Write: public WF_Block{
    std::string w_file;
public:
    WF_Write(int num, const std::string& filename);
    std::string* doBlock(std::string* in_text);
};


//Replace block
class WF_Replace: public WF_Block{
    std::string w_target;
    std::string w_new;
public:
    WF_Replace(int num, const std::string& words);
    std::string* doBlock(std::string* in_text);
};

//GREP Block
class WF_Grep: public WF_Block{
    std::string w_target;
public:
    WF_Grep(int num, const std::string& word);
    std::string* doBlock(std::string* in_text);
};

//Dump block
class WF_Dump: public WF_Block{
    std::string w_file;
public:
    WF_Dump(int num, const std::string& filename);
    std::string* doBlock(std::string* in_text);
};

//Sort Block
class WF_Sort: public WF_Block{
public:
    WF_Sort(int num);
    std::string* doBlock(std::string* in_text);
};

#endif //LAB2_WF_BLOCK_H
