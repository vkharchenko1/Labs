#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Trit.h"
#include "TritSet.h"

//trit
TEST_CASE("TRIT TESTING == and !=") {
    Trit value1 = Trit::Unknown;
    Trit value2 = Trit::Unknown;
    REQUIRE(value1 == value2);
    value2 = Trit::False;
    REQUIRE(value1 != value2);
    value2 = Trit::True;
    REQUIRE(value1 != value2);
    value1 = Trit::True;
    REQUIRE(value1 == value2);
    value2 = Trit::False;
    value1 = Trit::False;
    REQUIRE(value1 == value2);
}

TEST_CASE("TRIT TESTING &") {
    Trit value1 = Trit::Unknown;
    Trit value2 = Trit::Unknown;
    REQUIRE((value1 & value2) == Trit::Unknown);
    value1 = Trit::Unknown;
    value2 = Trit::False;
    REQUIRE((value1 & value2) == Trit::False);
    value1 = Trit::Unknown;
    value2 = Trit::True;
    REQUIRE((value1 & value2) == Trit::Unknown);
    value1 = Trit::False;
    value2 = Trit::False;
    REQUIRE((value1 & value2) == Trit::False);
    value1 = Trit::False;
    value2 = Trit::True;
    REQUIRE((value1 & value2) == Trit::False);
    value1 = Trit::True;
    value2 = Trit::True;
    REQUIRE((value1 & value2) == Trit::True);
}

TEST_CASE("TRIT TESTING |") {
    Trit value1 = Trit::Unknown;
    Trit value2 = Trit::Unknown;
    REQUIRE((value1 | value2) == Trit::Unknown);
    value1 = Trit::Unknown;
    value2 = Trit::False;
    REQUIRE((value1 | value2) == Trit::Unknown);
    value1 = Trit::Unknown;
    value2 = Trit::True;
    REQUIRE((value1 | value2) == Trit::True);
    value1 = Trit::False;
    value2 = Trit::False;
    REQUIRE((value1 | value2) == Trit::False);
    value1 = Trit::False;
    value2 = Trit::True;
    REQUIRE((value1 | value2) == Trit::True);
    value1 = Trit::True;
    value2 = Trit::True;
    REQUIRE((value1 | value2) == Trit::True);
}

TEST_CASE("TRIT TESTING ~") {
    Trit value = Trit::Unknown;
    REQUIRE((~value) == Trit::Unknown);
    value = Trit::True;
    REQUIRE((~value) == Trit::False);
    value = Trit::False;
    REQUIRE((~value) == Trit::True);
}

TEST_CASE("TRIT TESTING <<") {
    std::cout << "------- Trit << -------" << std::endl;
    Trit value = Trit::Unknown;
    std::cout << value << " " << Trit::Unknown << std::endl;
    value = Trit::True;
    std::cout << value << " " << Trit::True << std::endl;
    value = Trit::False;
    std::cout << value << " " << Trit::False << std::endl;
    std::cout << "-----------------------" << std::endl;
}

//reference
TEST_CASE("REFERENCE TESTING getTrit()") {
    TritSet set(100);
    REQUIRE(set[20].getTrit() == Trit::Unknown);
}

TEST_CASE("REFERENCE TESTING setTrit()") {
    TritSet set(100);
    set[20].setTrit(Trit::True);
    REQUIRE(set[20] == Trit::True);
}

TEST_CASE("REFERENCE TESTING =") {
    TritSet set(100);
    set[20] = Trit::True;
    REQUIRE(set[20] == Trit::True);
}

TEST_CASE("REFERENCE TESTING Trit()") {
    TritSet set(100);
    set[20] = Trit::True;
    Trit t = (Trit)set[20];
    REQUIRE(t == Trit::True);
}

TEST_CASE("REFERENCE TESTING &") {
    TritSet set(100);
    set[21] = Trit::False;
    set[22] = Trit::True;
    Trit value;

    value = set[20] & set[21];
    REQUIRE(value == Trit::False);
    set[25] = set[20] & set[22];
    REQUIRE(set[25] == Trit::Unknown);

    value = Trit::Unknown & set[21];
    REQUIRE(value == Trit::False);
    set[25] = Trit::Unknown & set[22];
    REQUIRE(set[25] == Trit::Unknown);

    value = set[20] & Trit::False;
    REQUIRE(value == Trit::False);
    set[25] = set[20] & Trit::True;
    REQUIRE(set[25] == Trit::Unknown);
}

TEST_CASE("REFERENCE TESTING |") {
    TritSet set(100);
    set[21] = Trit::False;
    set[22] = Trit::True;
    Trit value;

    value = set[20] | set[21];
    REQUIRE(value == Trit::Unknown);
    set[25] = set[20] | set[22];
    REQUIRE(set[25] == Trit::True);

    value = Trit::Unknown | set[21];
    REQUIRE(value == Trit::Unknown);
    set[25] = Trit::Unknown | set[22];
    REQUIRE(set[25] == Trit::True);

    value = set[20] | Trit::False;
    REQUIRE(value == Trit::Unknown);
    set[25] = set[21] | Trit::True;
    REQUIRE(set[25] == Trit::True);
}

TEST_CASE("REFERENCE TESTING ~") {
    TritSet set(100);
    set[21] = Trit::False;
    set[22] = Trit::True;
    Trit value;

    value = ~set[21];
    REQUIRE(value == Trit::True);
    set[25] = ~set[22];
    REQUIRE(set[25] == Trit::False);
}

TEST_CASE("REFERENCE TESTING == and !=") {
    TritSet set(100);
    set[21] = Trit::False;
    set[22] = Trit::True;
    Trit value = Trit::True;

    REQUIRE(set[21] != set[22]);
    REQUIRE(set[21] != value);
    REQUIRE(value != set[21]);
    REQUIRE(set[22] == value);
    REQUIRE(value == set[22]);
    REQUIRE(set[150] != Trit::True);
}

TEST_CASE("TRITSET TESTING &= and |=") {
    TritSet set(100);
    set[21] = Trit::False;
    set[22] = Trit::True;
    Trit value = Trit::False;

    set[22] &= set[21];
    REQUIRE(set[22] == Trit::False);
    set[20] &= value;
    REQUIRE(set[20] == Trit::False);

    value = Trit::True;
    set[20] |= value;
    REQUIRE(set[20] == Trit::True);
    set[21] |= set[19];
    REQUIRE(set[21] == Trit::Unknown);
}

//TritSet
TEST_CASE("TRITSET TESTING calcLength()") {
    TritSet a(100);
    REQUIRE(a.calcLength(8) == 1);
    REQUIRE(a.calcLength(9) == 1);
    REQUIRE(a.calcLength(16) == 1);
    REQUIRE(a.calcLength(17) == 2);
}

TEST_CASE("TRITSET TESTING []") {
    TritSet set(100);
    set[0] = Trit::True;
    set[1] = Trit::False;
    set[2] = Trit::True;
    REQUIRE(set[0] == Trit::True);
    REQUIRE(set[1] == Trit::False);
    REQUIRE(set[2] == Trit::True);
    set[15] = Trit::True;
    set[16] = Trit::False;
    set[17] = Trit::False;
    REQUIRE(set[15] == Trit::True);
    REQUIRE(set[16] == Trit::False);
    REQUIRE(set[17] == Trit::False);
    set[31] = Trit::False;
    set[32] = Trit::True;
    set[33] = Trit::True;
    REQUIRE(set[31] == Trit::False);
    REQUIRE(set[32] == Trit::True);
    REQUIRE(set[33] == Trit::True);
}

TEST_CASE("TRITSET TESTING copy") {
    TritSet t1(20);
    TritSet t2 = t1;
    TritSet t3;
    t3 = t1;
    t1 = t1;
    t2[5] = Trit::True;
    t3[5] = Trit::False;
    REQUIRE(t1[1] == t2[1]);
    REQUIRE(t1[5] != t2[5]);
    REQUIRE(t3[5] != t1[5]);
}

TEST_CASE("TRITSET TESTING capacity()") {
    TritSet set(100);
    REQUIRE(set.capacity() == 100);
    set[120] = Trit::Unknown;
    REQUIRE(set.capacity() == 100);
    if (set[120] != Trit::True)
        REQUIRE(set.capacity() == 100);
    set[120] = Trit::True;
    REQUIRE(set[120] == Trit::True);
    REQUIRE(set.capacity() == 121);
}

TEST_CASE("TRITSET TESTING length()") {
    TritSet set(100);
    REQUIRE(set.length() == 0);
    set[20] = Trit::True;
    REQUIRE(set.length() == 21);
    set[99] = Trit::False;
    REQUIRE(set.length() == 100);
    set[120] = Trit::True;
    REQUIRE(set.length() == 121);
}


TEST_CASE("TRITSET TESTING cardinality()") {
    TritSet set(100);
    REQUIRE(set.cardinality(Trit::Unknown) == 100);
    REQUIRE(set.cardinality(Trit::True) == 0);
    REQUIRE(set.cardinality(Trit::False) == 0);

    for (int i = 0; i < 20; i++)
        set[i] = Trit::False;
    for (int i = 20; i < 40; i++)
        set[i] = Trit::True;

    REQUIRE(set.cardinality(Trit::Unknown) == 60);
    REQUIRE(set.cardinality(Trit::True) == 20);
    REQUIRE(set.cardinality(Trit::False) == 20);

    std::unordered_map <Trit, int> trits;
    std::unordered_map <Trit, int> check = {{Trit::True, 20}, {Trit::False, 20}, {Trit::Unknown, 60}};
    trits = set.cardinality();
    REQUIRE(check == trits);
}

TEST_CASE("TRITSET TESTING expand()") {
    TritSet set(100);
    set.expand(120);
    REQUIRE(set.capacity() == 121);
}

TEST_CASE("TRITSET TESTING trim()") {
    TritSet set(100);
    set[40] = Trit::False;
    set[90] = Trit::True;
    set.trim(50);
    REQUIRE(set[90] == Trit::Unknown);
    REQUIRE(set.capacity() == 51);
    REQUIRE(set.length() == 41);
}

TEST_CASE("TRITSET TESTING shrink()") {
    TritSet set(100);
    set[40] = Trit::False;
    set.shrink();
    REQUIRE(set.capacity() == 41);
}

TEST_CASE("TRITSET TESTING &") {
    TritSet set1(100);
    TritSet set2(40);
    for (int i = 0; i < 40; i++)
        set2[i] = Trit::False;
    for (int i = 0; i < 100; i++)
        set1[i] = Trit::True;
    TritSet set3 = set1 & set2;
    for (int i = 0; i < 40; i++)
        REQUIRE(set3[i] == Trit::False);
    for (int i = 40; i < 100; i++) {
        std::cout << i << ' ' << set3[i] << std::endl;
        REQUIRE(set3[i] == Trit::Unknown);
    }
}