#include "TritSet.h"

//reference
TritSet::reference::reference(TritSet *base, uint index) {
    r_base = base;
    r_index = index;
    r_value = Trit::Unknown;

    if (index < base->t_length) {
        uint slot = index / 4 / sizeof(uint);   // номер трита / кол-во тритов в байте / кол-во байт в uint
        uint bit = (index * 2) % (8 * sizeof(uint));   // номер бита в массиве % кол-во бит в одном слоте

        uint value = 0;
        value |= r_base->t_data[slot] >> bit;
        value &= 3;
        r_value = (Trit)value;
    }
}

void TritSet::reference::setTrit(Trit value) {
    r_value = value;

    if (r_index > r_base->t_length) {
        if (value == Trit::Unknown)
            return;
        r_base->expand(r_index);
    }


    uint slot = r_index / 4 / sizeof(uint);   // номер трита / кол-во тритов в байте / кол-во байт в uint
    uint bit = (r_index * 2) % (8 * sizeof(uint));   // номер бита в массиве % кол-во бит в одном слоте

    uint carry = (uint)value;
    carry <<=  sizeof(uint) * 8 - 2 - bit;
    uint nullifier = ~(3 << (sizeof(uint) * 8 - 2 - bit));

    r_base->t_data[slot] &= nullifier;
    r_base->t_data[slot] |= carry;
}

Trit TritSet::reference::getTrit() {
    return r_value;
}

TritSet::reference::operator Trit() {
    return r_value;
}

TritSet::reference& TritSet::reference::operator=(Trit value) {
    r_value = value;
    setTrit(r_value);
    return *this;
}

bool TritSet::reference::operator==(Trit value) {
    return r_value == value;
}

bool TritSet::reference::operator!=(Trit value) {
    return r_value != value;
}

Trit TritSet::reference::operator~() {
    return (Trit)(3 - (uint)r_value);
}

Trit TritSet::reference::operator&(Trit value) {
    if (r_value < value)
        return r_value;
    return value;
}

Trit TritSet::reference::operator|(Trit value) {
    if (r_value > value)
        return r_value;
    return value;
}

//TritSet
uint TritSet::calcLength(uint num_of_trits) {
    uint num_of_bits = num_of_trits * 2;
    uint num_of_bytes = (num_of_bits + 7) / 8;
    uint size_of_set = (num_of_bytes + sizeof(uint) - 1) / sizeof(uint);
    return size_of_set;
}

TritSet::TritSet() {
    t_length = 0;
    t_data = nullptr;
}

TritSet::TritSet(uint num_of_trits) {
    t_length = num_of_trits;
    uint size_of_set = calcLength(num_of_trits);
    t_data = new uint[size_of_set];
    memset(t_data, 0, size_of_set / sizeof(uint));
}

uint TritSet::capacity() const{
    return t_length;
}

uint TritSet::length() {
    uint last_index = 0;
    for (int i = 0; i < t_length; i++) {
        if ((*this)[i] != Trit::Unknown)
            last_index = i;
    }
    return last_index + 1;
}

int TritSet::cardinality(Trit value) {
    int count = 0;
    for (int i = 0; i < t_length; i++) {
        if ((*this)[i] == value)
            count++;
    }
    return count;
}

std::unordered_map <Trit, int> TritSet::cardinality(){
    std::unordered_map <Trit, int> trits;
    trits.insert(std::make_pair<Trit, int>(Trit::True, cardinality(Trit::True)));
    trits.insert(std::make_pair<Trit, int>(Trit::Unknown, cardinality(Trit::Unknown)));
    trits.insert(std::make_pair<Trit, int>(Trit::False, cardinality(Trit::False)));

    return trits;
}

TritSet::reference TritSet::operator[](uint index) {
    reference t_trit(this, index);
    return t_trit;
}

void TritSet::expand(uint new_end) {
    uint new_size = calcLength(new_end);
    uint* new_data = new uint[new_size];

    uint size_of_set = calcLength(t_length);
    std::copy(t_data, t_data + size_of_set - 1, new_data);

    t_length = new_end;
    delete [] t_data;
    t_data = new_data;
}

void TritSet::trim(uint last_index) {
    uint new_size = calcLength(last_index);
    uint* new_data = new uint[new_size];

    std::copy(t_data, t_data + new_size - 1, new_data);

    t_length = last_index;
    delete [] t_data;
    t_data = new_data;
}

void TritSet::shrink() {
    uint last_index = this->length();

    uint new_size = calcLength(last_index);
    uint* new_data = new uint[new_size];

    std::copy(t_data, t_data + new_size - 1, new_data);

    t_length = last_index;
    delete [] t_data;
    t_data = new_data;
}

TritSet::~TritSet() {
    delete []t_data;
}

TritSet TritSet::operator&(TritSet set) {
    uint new_size = std::max(t_length, set.length());
    TritSet res(new_size);
    for (int i = 0; i < new_size; i++)
        res[i] = (*this)[i] & set[i];
    return res;
}

TritSet TritSet::operator|(TritSet set) {
    uint new_size = std::max(t_length, set.length());
    TritSet res(new_size);
    for (int i = 0; i < new_size; i++)
        res[i] = (*this)[i] | set[i];
    return res;
}

TritSet TritSet::operator~() {
    TritSet res(t_length);
    for (int i = 0; i < t_length; i++)
        res[i] = ~(*this)[i];
    return res;
}

TritSet::TritSet(const TritSet& t) {
    t_length = t.t_length;
    t_data = new uint[t_length];

    uint size = calcLength(t_length);

    std::copy(t.t_data, t.t_data + size - 1, t_data);
}