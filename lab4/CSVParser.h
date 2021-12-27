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
void getTuple(std::tuple<Args...>* new_tuple, std::index_sequence<I...>, std::stringstream *ss, char delimiter) {
    (..., (getTupleImpl<I>(new_tuple, ss, delimiter)));
}

template<class... Args>
class CSVIterator: public std::iterator<std::input_iterator_tag, std::tuple<Args...>>
{
    friend class CSVParser<Args...>;
    typename std::vector<std::tuple<Args...>>::iterator base;
public:
    CSVIterator(typename std::vector<std::tuple<Args...>>::iterator b) {
        base = b;
    }
    CSVIterator(const CSVIterator &t) {
        base = t.base;
    }
    bool operator!=(CSVIterator const& other) const {
        return base != other.base;
    }
    bool operator==(CSVIterator const& other) const {
        return base == other.base;
    }
    std::tuple<Args...> operator*() const {
        return *base;
    }
    CSVIterator& operator++() {
        base++;
        return *this;
    }
};

template <class... Args>
class CSVParser {
public:
    std::vector<std::tuple<Args...>> csv_tuples;
    CSVParser(std::ifstream& file, int skip) {
        std::string line;

        for (int i = 0; i < skip; i ++) {
            if (!std::getline(file, line)) {
                std::cout << "Lines skip over end of file" << std::endl;
            }
        }

        while(!file.eof()) {
            std::getline(file, line);
            std::tuple<Args...> new_tuple;
            std::stringstream ss(line);

            auto I = std::make_index_sequence<std::tuple_size_v<std::tuple<Args...>>>{};
            getTuple(&new_tuple, I, &ss, ',');
            csv_tuples.push_back(new_tuple);
        }
    }

    typedef CSVIterator<Args...> iterator;

    iterator begin() {
        return iterator(csv_tuples.begin());
    }
    iterator end() {
        return iterator(csv_tuples.end());
    }
};

#endif //LAB4_CSVPARSER_H
