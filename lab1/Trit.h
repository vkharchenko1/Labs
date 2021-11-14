#ifndef TRIT_H
#define TRIT_H

typedef unsigned int uint;

//класс тритов
enum class Trit {
    Unknown = 0,
    False = 1,
    True = 2
};

//проверка на равенство
bool operator==(Trit value1, Trit value2);

//проверка на неравенство
bool operator!=(Trit value1, Trit value2);

//логическое "не"
Trit operator~(Trit value);

//логическое "и"
Trit operator&(Trit value1, Trit value2);

//логическое "или"
Trit operator|(Trit value1, Trit value2);

#endif //TRIT_H
