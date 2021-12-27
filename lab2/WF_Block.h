#ifndef LAB2_WF_BLOCK_H
#define LAB2_WF_BLOCK_H

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "WF_Exception.h"

//Parent Block
class WF_Block {
protected:
    WF_Block() = default;;
public:
    virtual ~WF_Block() = default;
    virtual std::string* doBlock(std::string* in_text) = 0;
};

//Reading Block
class WF_Read: public WF_Block{
    std::string w_file;
public:
    explicit WF_Read(const std::string& filename);
    ~WF_Read() override = default;
    std::string* doBlock(std::string* in_text) override;
};

//Writing Block
class WF_Write: public WF_Block{
    std::string w_file;
public:
    explicit WF_Write(const std::string& filename);
    ~WF_Write() override = default;
    std::string* doBlock(std::string* in_text) override;
};


//Replace block
class WF_Replace: public WF_Block{
    std::string w_target;
    std::string w_new;
public:
    explicit WF_Replace(const std::string& words);
    ~WF_Replace() override = default;
    std::string* doBlock(std::string* in_text) override;
};

//GREP Block
class WF_Grep: public WF_Block{
    std::string w_target;
public:
    explicit WF_Grep(const std::string& word);
    ~WF_Grep() override = default;
    std::string* doBlock(std::string* in_text) override;
};

//Dump block
class WF_Dump: public WF_Block{
    std::string w_file;
public:
    explicit WF_Dump(const std::string& filename);
    ~WF_Dump() override = default;
    std::string* doBlock(std::string* in_text) override;
};

//Sort Block
class WF_Sort: public WF_Block{
public:
    explicit WF_Sort() = default;
    ~WF_Sort() override = default;
    std::string* doBlock(std::string* in_text) override;
};

#endif //LAB2_WF_BLOCK_H
