#ifndef TRITSET_H
#define TRITSET_H

#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include "Trit.h"

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
        reference(const TritSet* base, uint index);

        //приведение к Trit
        operator Trit();
        operator Trit() const;

        //вставить трит
        void setTrit(Trit value);
        //получить трит
        [[nodiscard]] Trit getTrit() const;

        //присваивание
        reference& operator=(Trit value);
    };

    //вычислить длину t_data
    static uint calcLength(uint num_of_trits);

    //объявление и деструктор
    TritSet();
    explicit TritSet(uint num_of_trits);
    ~TritSet();

    //обращение к элементу
    reference operator[](uint index);
    Trit operator[](uint index) const;
    //копирование тритсета
    TritSet(const TritSet& t);
    TritSet& operator=(const TritSet& t);

    //количественные показатели тритсета
    [[nodiscard]] uint capacity() const;
    [[nodiscard]] uint length() const;
    [[nodiscard]] int cardinality(Trit value) const;
    [[nodiscard]] std::unordered_map<Trit, int> cardinality() const;

    //расширение и уменьшение тритсета
    void expand(uint new_end);
    void trim(uint last_index);
    void shrink();

    //потритовые операции
    TritSet operator|(TritSet set);
    TritSet operator~();
};

TritSet operator&(const TritSet& set1, const TritSet& set2);

//присваивание с операцией
TritSet::reference& operator&=(TritSet::reference ref, Trit value);
TritSet::reference& operator|=(TritSet::reference ref, Trit value);

#endif //TRITSET_H