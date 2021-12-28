#ifndef LAB4_CSVPARSER_H
#define LAB4_CSVPARSER_H

#include <tuple>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

template <class... Args> class CSVParser;

template<size_t I, class...Args>
void getTupleImpl(std::tuple<Args...>* new_tuple, std::stringstream *ss, char delimiter) {
    char ch;
    std::string l;
    while (ss->peek() != delimiter) {
        if (ss->eof())
            break;
        ss->get(ch);
        l += ch;
    }
    if (!ss->eof())
        ss->get(ch);
    std::stringstream st(l);
    st >> std::get<I>(*new_tuple);
}

template<class...Args, size_t...I>
void getTuple(std::tuple<Args...>* new_tuple, std::index_sequence<I...>, std::stringstream* ss, char delimiter) {
    (..., (getTupleImpl<I>(new_tuple, ss, delimiter)));
}

template<class... Args>
class CSVIterator: public std::iterator<std::input_iterator_tag, std::tuple<Args...>>
{
    friend class CSVParser<Args...>;
    std::ifstream* csv_file;
    std::streampos csv_pos;
public:
    explicit CSVIterator(std::ifstream* file) {
        csv_file = file;
        csv_pos = csv_file->tellg();

        csv_file->seekg(0);
    }
    CSVIterator(const CSVIterator &t) {
        t.csv_file->seekg(t.csv_pos);
        csv_file = t.csv_file;
        csv_pos = t.csv_pos;

    }
    bool operator!=(CSVIterator const& other) const {

        return csv_pos != other.csv_pos;
    }
    bool operator==(CSVIterator const& other) const {

        return csv_pos == other.csv_pos;
    }
    std::tuple<Args...> operator*() const {
        csv_file->seekg(csv_pos);

        std::string line;
        getline(*csv_file, line);

        std::tuple<Args...> line_tuple;
        std::stringstream ss(line);
        auto I = std::make_index_sequence<std::tuple_size_v<std::tuple<Args...>>>{};

        getTuple(&line_tuple, I, &ss, ',');

        return line_tuple;
    }

    CSVIterator& operator++() {

        csv_file->seekg(csv_pos);

        std::string throw_away;
        getline(*csv_file, throw_away);

        if (csv_file->eof()) {
            csv_file->clear();
            csv_file->seekg(0, std::ios_base::end);
        }
        csv_pos = csv_file->tellg();

        return *this;
    }
};

template <class... Args>
class CSVParser {
    std::ifstream* csv_file;
    std::streampos csv_begin;
public:
    CSVParser(std::ifstream& file, int skip) {
        std::string line;

        for (int i = 0; i < skip; i ++) {
            if (!std::getline(file, line)) {
                std::cout << "Lines skip over end of file" << std::endl;
                exit(0);
            }
        }
        csv_file = &file;
        csv_begin = csv_file->tellg();

    }

    CSVIterator<Args...> begin() {
        csv_file->seekg(csv_begin);

        return CSVIterator<Args...>(csv_file);
    }
    CSVIterator<Args...> end() {
        csv_file->seekg(0, std::ios_base::end);

        return CSVIterator<Args...>(csv_file);
    }
};

#endif //LAB4_CSVPARSER_H
