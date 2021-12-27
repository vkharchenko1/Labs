#include "WF_Block.h"

//Reading block
WF_Read::WF_Read(const std::string& filename) {
    w_file = filename;
}

std::string* WF_Read::doBlock(std::string* in_text) {
    if (in_text)
        throw WF_Exception("Text passed to Read block\n");
    std::ifstream in_file;
    in_file.open(w_file);

    std::string str;
    std::string* out_text;
    std::string* trans_text;
    
    int count = 0;
    out_text = new std::string[1];
    trans_text = new std::string[1];
    out_text[0] = "0";
    trans_text[0] = "0";

    while (!in_file.eof()) {
        std::getline(in_file, str);
        count++;

        delete[] out_text;
        out_text = new std::string[count + 1];

        out_text[0] = std::to_string(count);
        out_text[count] = str;

        for (int i = 1; i < count; i++) {
            out_text[i] = trans_text[i];
        }

        delete[] trans_text;
        trans_text = new std::string[count + 1];

        for (int i = 0; i <= count; i++) {
            trans_text[i] = out_text[i];
        }
    }

    delete[] trans_text;
    in_file.close();
    return out_text;
}

//Writing Block
WF_Write::WF_Write(const std::string& filename) {
    w_file = filename;
}
        
std::string* WF_Write::doBlock(std::string* in_text) {
    if (!in_text)
        throw WF_Exception("No text passed to Write block\n");
    std::ofstream out_file;
    out_file.open(w_file);
    
    int count = std::stoi(in_text[0]);

    out_file << in_text[1];
    for (int i = 2; i <= count; i++) {
        if (in_text[i].empty() || in_text[i].back() != '\n') {
            out_file << std::endl;
        }
        out_file << in_text[i];
    }

    delete[] in_text;
    out_file.close();
    return nullptr;
}

//Replace Block
WF_Replace::WF_Replace(const std::string& words) {
    w_target = "";
    w_new = "";

    int input_mode = 0;
    for (auto letter : words) {
        if (isdigit(letter) || isalpha(letter)) {
            if (input_mode == 0)
                w_target += letter;
            else if (input_mode == 1)
                w_new += letter;
            else
                throw WF_Exception("Too many arguments in Replace initialization\n");
        }
        else {
            if (input_mode == 2)
                break;
            input_mode++;
        }
    }

    if (w_target.empty() || w_new.empty()) {
        throw WF_Exception("Too few arguments in Replace block initialization\n");
    }
}

std::string* WF_Replace::doBlock(std::string *in_text) {
    if (!in_text)
        throw WF_Exception("No text passed to Replace block\n");
    int count = std::stoi(in_text[0]);
    size_t start;

    for (int i = 1; i <= count; i++) {
        while ((start = in_text[i].find(w_target)) != std::string::npos) {
            in_text[i].replace(start, w_target.length(), w_new);
        }
    }

    return in_text;
}

//Grep Block
WF_Grep::WF_Grep(const std::string &word) {
    w_target = "";

    int input_mode = 0;
    for (auto letter : word) {
        if (isdigit(letter) || isalpha(letter)) {
            if (input_mode == 0)
                w_target += letter;
            else
                throw WF_Exception("Too many arguments in Grep block initialization\n");
        }
        else {
            if (input_mode == 1)
                break;
            input_mode++;
        }
    }

    if (w_target.empty()) {
        throw WF_Exception("Too few arguments in Grep block initialization\n");
    }
}

std::string *WF_Grep::doBlock(std::string *in_text) {
    if (!in_text)
        throw WF_Exception("No text passed to Grep block\n");
    int in_size = std::stoi(in_text[0]);
    std::string* collecting_text = new std::string[in_size];
    int out_size = 0;

    for (int i = 1; i <= in_size; i++) {
        if (in_text[i].find(w_target) != std::string::npos) {
            collecting_text[out_size] = in_text[i];
            out_size++;
        }
    }

    std::string* out_text = new std::string[out_size + 1];
    out_text[0] = std::to_string(out_size);

    for (int i = 1; i <= out_size; i++) {
        out_text[i] = collecting_text[i - 1];
    }

    delete[] in_text;
    delete[] collecting_text;
    return out_text;
}

//Dump Block
WF_Dump::WF_Dump(const std::string &filename) {
    w_file = filename;
}

std::string *WF_Dump::doBlock(std::string *in_text) {
    if (!in_text)
        throw WF_Exception("No text passed to Dump block\n");
    std::ofstream out_file;
    out_file.open(w_file);

    int count = std::stoi(in_text[0]);

    out_file << in_text[1];
    for (int i = 2; i <= count; i++) {
        if (in_text[i].empty() || in_text[i].back() != '\n') {
            out_file << std::endl;
        }
        out_file << in_text[i];
    }

    out_file.close();
    return in_text;
}

//Sort Block
std::string *WF_Sort::doBlock(std::string *in_text) {
    if (!in_text)
        throw WF_Exception("No text passed to Sort block\n");
    int count = std::stoi(in_text[0]);
    std::sort(&in_text[1], &in_text[count] + 1);
    return in_text;
}
