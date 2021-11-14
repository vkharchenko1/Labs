#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Trit.h"
#include "TritSet.h"

//trit
TEST_CASE("TESTING == and !=") {
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

TEST_CASE("TESTING &") {
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

TEST_CASE("TESTING |") {
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

TEST_CASE("TESTING ~") {
    Trit value = Trit::Unknown;
    REQUIRE((~value) == Trit::Unknown);
    value = Trit::True;
    REQUIRE((~value) == Trit::False);
    value = Trit::False;
    REQUIRE((~value) == Trit::True);
}

//reference


//TritSet
TEST_CASE("TESTING calcLength()") {
    TritSet a(100);
    REQUIRE(a.calcLength(8) == 1);
    REQUIRE(a.calcLength(9) == 1);
    REQUIRE(a.calcLength(16) == 2);
    REQUIRE(a.calcLength(17) == 2);
}

TEST_CASE("TESTING TritSet()") {
    TritSet set(100);
    REQUIRE(set[20] == Trit::Unknown);
}