#include <iostream>
#include <cassert>
#include <vector>

#include "proxy_containers.hpp"

using namespace proxy_containers;

const_array<int> fn(const std::vector<int>& v) {
    return const_array<int> {v};
}

const_array<int> fn2(const const_array<int>& v) {
    return v;
}

void main2() {
    constexpr std::array<int, 2> array1 {{1, 2}};
    constexpr std::array<int, 2> array2 {{1, 3}};
    constexpr std::array<int, 3> array3 {{1, 2, 3}};
    constexpr std::array<int, 1> array4 {{1}};
    constexpr std::array<int, 1> array5 {{2}};

    static_assert(const_array<int> {array1}.size() == 2, "");
    static_assert(const_array<int> {array5}.size() == 1, "");

    static_assert(const_array<int> {array1} == array1, "");
    static_assert(array1 == const_array<int> {array1}, "");
    static_assert(const_array<int> {array1} <= array1, "");
    static_assert(const_array<int> {array1} >= array1, "");

    static_assert(const_array<int> {array1} != array2, "");
    static_assert(const_array<int> {array1} != array3, "");
    static_assert(const_array<int> {array1} != array4, "");

    static_assert(const_array<int> {array1} < array2, "");
    static_assert(const_array<int> {array1} < array3, "");
    static_assert(const_array<int> {array1} > array4, "");

    static_assert(const_array<int> {array1} <= array2, "");
    static_assert(const_array<int> {array1} <= array3, "");

    static_assert(const_array<int> {array1}.contains(array1), "");
    static_assert(!const_array<int> {array1}.contains(array2), "");
    static_assert(!const_array<int> {array1}.contains(array3), "");
    static_assert(const_array<int> {array1}.contains(array4), "");
    static_assert(const_array<int> {array1}.contains(array5), "");
    static_assert(const_array<int> {array1}.contains(const_array<int> {1}), "");
    static_assert(const_array<int> {array1}.find(const_array<int> {1}) == 0, "");
    static_assert(const_array<int> {array1}.find(const_array<int> {2}) == 1, "");
    static_assert(const_array<int> {array1}.find(1) == 0, "");
    static_assert(const_array<int> {array1}.find(2) == 1, "");
    static_assert(const_array<int> {array1}.find(3) == const_array<int>::npos, "");
    static_assert(const_array<int> {1}.in(const_array<int> {array1}), "");
    static_assert(!const_array<int> {3}.in(const_array<int> {array1}), "");
    static_assert(!const_array<int> {3}.in(array1), "");

    const std::vector<int> arr1 = {1, 2};
    const std::vector<int> arr2 = {1, 3};
    const std::vector<int> arr3 = {1, 2, 3};
    const std::vector<int> arr4 = {1};

    assert(const_array<int> {arr1}.size() == 2);

    assert(const_array<int> {arr1} == arr1);
    assert(arr1 == const_array<int> {arr1});
    assert(const_array<int> {arr1} != arr2);
    assert(const_array<int> {arr1} != arr3);
    assert(const_array<int> {arr1} != arr4);

    assert(std::vector<int> (const_array<int> {arr1}.begin(),
                             const_array<int> {arr1}.end()).size() == 2);
    assert(fn(arr1) == const_array<int> {arr1});
    assert(fn(arr1) == arr1);
    assert(fn(arr1) != arr2);
    assert(fn2(arr1) == const_array<int>{arr1});

    std::cout << const_array<int> {arr1};
    std::cout << std::endl;

    std::vector<int> vs;
    for (std::size_t i = 0; i < 10e3; ++i) { // only 1000 elems in c++14 recursive method
        vs.emplace_back(i);
    }
    assert(const_array<int> {vs}.find(1000) == 1000);
    assert(const_array<int> {vs}.find(-1) == const_array<int>::npos);
}

int main() {
    static constexpr const_string strings[] = {
        "abcdddmmmnnncvnbcb",
        "aaa",
        "fff",
        "bbb",
        "ccc"
    };

    static_assert(strings[0].substr(0, 3) == strings[0].substr(0, 3), "");

    static_assert(const_string {strings[0].data(), 5}.size() == 5, "");
    static_assert(const_string {strings[0].substr(0, 3)}.size() == 3, "");
    static_assert(const_string {strings[0]}.size() == 18, "");
    static_assert(const_string {strings[1]}.size() == 3, "");
    static_assert(const_string {strings[0].substr(15)}.size() == 3, "");
    static_assert(const_string {strings[0].substr(15)} == "bcb", "");
    static_assert(const_string {strings[0].substr(0, 3)} == strings[0].substr(0, 3), "");
    static_assert(const_string {strings[0].substr(0, 3)} == const_string {"abc"}, "");

    static_assert(const_string {"ddd"} == const_string {"ddd"}, "");
    static_assert(const_string {"dda"} != const_string {"ddd"}, "");
    static_assert(const_string {"abc"} <  const_string {"aqq"}, "");
    static_assert(const_string {"Abc"} <  "abc", "");
    static_assert(const_string {"qbc"} == "qbc", "");
    static_assert(const_string {"abc"} <  const_string {"qwee"}, "");
    static_assert(const_string {"abc"} <  const_string {"qaa"}, "");
    static_assert(const_string {"abc"} >= const_string {"abb"}, "");
    static_assert(const_string {"qbc"} >= const_string {"qbc"}, "");
    static_assert(const_string {"qbc"} == const_string {"qbc"}, "");
    static_assert(const_string {"qbc"} >= const_string {"qbc"}, "");
    static_assert(const_string {"qbd"} >  const_string {"qbc"}, "");
    static_assert(const_string {"qbd"} >= const_string {"qbc"}, "");
    static_assert(const_string {"abc"} <= const_string {"qwee"}, "");
    static_assert(const_string {"abc"} <= const_string {"abc"}, "");

    static_assert(const_string {"Abc"}.at(1) == 'b', "");
    static_assert(const_string {"Abc"}[1] == 'b', "");

    static_assert(const_string {"HelloWorld"}.contains("HelloWorld"), "");
    static_assert(const_string {"HelloWorld"}.contains("Hello"), "");
    static_assert(const_string {"HelloWorld"}.contains("World"), "");
    static_assert(const_string {"HelloWorld"}.contains("ld"), "");
    static_assert(const_string {"Hello"}.contains("H"), "");
    static_assert(const_string {"Hello"}.contains(const_string{"H"}), "");
    static_assert(const_string {"Hello"}.contains("o"), "");
    static_assert(not const_string {"Hello"}.contains("z"), "");
    static_assert(not const_string {"HelloWorld"}.contains("Worlddddd"), "");
    static_assert(not const_string {"HelloWorld"}.contains("HelloWorld!"), "");
    static_assert(not const_string {"Hello"}.contains("HelloWorld"), "");
    static_assert(const_string {"o"}.in("Hello"), "");
    static_assert(const_string {"llo"}.in("Hello"), "");

    static_assert(const_string {"Hello"}.find("Z") == const_string::npos, "");
    static_assert(const_string {"Hello"}.find("H") == 0, "");
    static_assert(const_string {"Hello"}.find("e") == 1, "");
    static_assert(const_string {"Hello"}.find("o") == 4, "");
    static_assert(const_string {"Hello"}.find('o') == 4, "");
    static_assert(const_string {"Hello"}.find(const_string {"o"}) == 4, "");

    assert(const_string {"abc"} == std::string {"abc"});
    assert(std::string {"abc"} == const_string {"abc"});
    assert(not (const_string {"abc"} != std::string {"abc"}));
    assert(const_string {"Hello"}.contains(std::string{"H"}));
    assert(const_string {"o"}.in(std::string {"Hello"}));
    assert(not const_string {"o"}.in(std::string {"Hell"}));
    assert(const_string {"Hello"}.find(std::string {"o"}) == 4);

    const std::string stdstr {"hello"};
    const const_string str {stdstr};
    assert(str == "hello");
    assert(str.at(2) == 'l');

    assert(const_string {std::string {"my std string"}} == "my std string");

    constexpr const_string s {"Hello"};
    constexpr const_string s2 {s};

    std::cout << "s2 = " << s2 << std::endl;

    for (const auto& param : strings)
        std::cout << param << '\n';

    for (auto ch : strings[0]) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;

    std::cout << const_string {strings[0].substr(0, 3)} << '\n';

    main2();

    return 0;
}
