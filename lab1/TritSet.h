#ifndef TRITSET_H
#define TRITSET_H

#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include "Trit.h"

typedef unsigned int uint;

//класс массива тритов
class TritSet {
private:
    uint t_length;
    uint* t_data;

public:
    //класс элемента тритсета
    class reference {
        Trit r_value;
        uint r_index;
        TritSet* r_base;

    public:
        //объявление
        reference(TritSet* base, uint index);

        //вставить трит
        void setTrit(Trit value);
        //получить трит
        Trit getTrit();

        //приведение к Trit
        operator Trit();
        //присваивание
        reference& operator=(Trit value);

        //проверка на равенство
        bool operator==(Trit value);
        //проверка на неравенство
        bool operator!=(Trit value);

        //логическое "не"
        Trit operator~();
        //логическое "и"
        Trit operator&(Trit value);
        //логическое "или"
        Trit operator|(Trit value);
    };

    //вычислить длину t_data
    static uint calcLength(uint num_of_trits);

    //объявление и деструктор
    TritSet();
    explicit TritSet(uint num_of_trits);
    ~TritSet();

    //обращение к элементу
    reference operator[](uint index);
    //копирование тритсета
    TritSet(const TritSet& t);

    //количественные показатели тритсета
    uint capacity() const;
    uint length();
    int cardinality(Trit value);
    std::unordered_map<Trit, int> cardinality();

    //расширение и уменьшение тритсета
    void expand(uint new_end);
    void trim(uint last_index);
    void shrink();

    //потритовые операции
    TritSet operator&(TritSet set);
    TritSet operator|(TritSet set);
    TritSet operator~();
};

#endif //TRITSET_H