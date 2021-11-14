#include "Trit.h"

bool operator==(Trit value1, Trit value2) {
    return (uint)value1 == (uint)value2;
}

bool operator!=(Trit value1, Trit value2) {
    return (uint)value1 != (uint)value2;
}

Trit operator~(Trit value) {
    return (Trit)((3 - (uint)value)%3);
}

Trit operator&(Trit value1, Trit value2) {
    if (value1 == Trit::False || value2 == Trit::False)
        return Trit::False;
    if (value1 == Trit::Unknown || value2 == Trit::Unknown)
        return Trit::Unknown;
    return Trit::True;
}

Trit operator|(Trit value1, Trit value2) {
    if (value1 == Trit::True || value2 == Trit::True)
        return Trit::True;
    if (value1 == Trit::Unknown || value2 == Trit::Unknown)
        return Trit::Unknown;
    return Trit::False;
}