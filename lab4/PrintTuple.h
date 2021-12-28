#ifndef LAB4_PRINTTUPLE_H
#define LAB4_PRINTTUPLE_H

#include <iostream>
#include <tuple>

template <typename Arg, typename... Args>
std::tuple<Args...> tuple_tail(const std::tuple<Arg, Args...>& t)
{
    return apply([](auto arg, auto... args) {return std::make_tuple(args...);}, t);
}

template<class Ch, class Tr, class Arg>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Arg> const& t) {
    os << std::get<0>(t);
}

template<class Ch, class Tr, class Arg, class... Args>
void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Arg, Args...> const& t) {
    printTuple(os, std::make_tuple(std::get<    0>(t)));
    os << ", ";
    printTuple(os, tuple_tail(t));
}

template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t)
-> std::basic_ostream<Ch, Tr>& {
    os << "(";
    printTuple(os, t);
    os << ")";
    return os;
}

#endif //LAB4_PRINTTUPLE_H
