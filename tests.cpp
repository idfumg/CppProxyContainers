#include <iostream>
#include <cassert>
#include <vector>

#include "proxy_containers.hpp"

using namespace proxy_containers;

array_view<int> fn(const std::vector<int>& v) {
    return array_view<int> {v};
}

array_view<int> fn2(const array_view<int>& v) {
    return v;
}

void main2() {
    constexpr std::array<int, 2> array1 {{1, 2}};
    constexpr std::array<int, 2> array2 {{1, 3}};
    constexpr std::array<int, 3> array3 {{1, 2, 3}};
    constexpr std::array<int, 1> array4 {{1}};
    constexpr std::array<int, 1> array5 {{2}};

    static_assert(array_view<int> {array3}[2] == 3, "");
    static_assert(array_view<int> {array3}.subarray(2) == array_view<int> {3}, "");

    static_assert(array_view<int> {array1}.size() == 2, "");
    static_assert(array_view<int> {array5}.size() == 1, "");

    static_assert(array_view<int> {array1} == array1, "");
    static_assert(array1 == array_view<int> {array1}, "");
    static_assert(array_view<int> {array1} <= array1, "");
    static_assert(array_view<int> {array1} >= array1, "");

    static_assert(array_view<int> {array1} != array2, "");
    static_assert(array_view<int> {array1} != array3, "");
    static_assert(array_view<int> {array1} != array4, "");

    static_assert(array_view<int> {array1} < array2, "");
    static_assert(array_view<int> {array1} < array3, "");
    static_assert(array_view<int> {array1} > array4, "");

    static_assert(array_view<int> {array1} <= array2, "");
    static_assert(array_view<int> {array1} <= array3, "");

    static_assert(array_view<int> {array1}.contains(array1), "");
    static_assert(!array_view<int> {array1}.contains(array2), "");
    static_assert(!array_view<int> {array1}.contains(array3), "");
    static_assert(array_view<int> {array1}.contains(array4), "");
    static_assert(array_view<int> {array1}.contains(array5), "");
    static_assert(array_view<int> {array1}.contains(array_view<int> {1}), "");
    static_assert(array_view<int> {array1}.find(array_view<int> {1}) == 0, "");
    static_assert(array_view<int> {array1}.find(array_view<int> {2}) == 1, "");
    static_assert(array_view<int> {array1}.find(1) == 0, "");
    static_assert(array_view<int> {array1}.find(2) == 1, "");
    static_assert(array_view<int> {array1}.find(3) == array_view<int>::npos, "");
    static_assert(array_view<int> {1}.in(array_view<int> {array1}), "");
    static_assert(!array_view<int> {3}.in(array_view<int> {array1}), "");
    static_assert(!array_view<int> {3}.in(array1), "");

    const std::vector<int> arr1 = {1, 2};
    const std::vector<int> arr2 = {1, 3};
    const std::vector<int> arr3 = {1, 2, 3};
    const std::vector<int> arr4 = {1};

    assert(array_view<int> {arr1}.size() == 2);

    assert(array_view<int> {arr1} == arr1);
    assert(arr1 == array_view<int> {arr1});
    assert(array_view<int> {arr1} != arr2);
    assert(array_view<int> {arr1} != arr3);
    assert(array_view<int> {arr1} != arr4);
    assert(array_view<int> {1}.in(arr1));

    assert(std::vector<int> (array_view<int> {arr1}.begin(),
                             array_view<int> {arr1}.end()).size() == 2);
    assert(fn(arr1) == array_view<int> {arr1});
    assert(fn(arr1) == arr1);
    assert(fn(arr1) != arr2);
    assert(fn2(arr1) == array_view<int>{arr1});

    std::cout << array_view<int> {arr1};
    std::cout << std::endl;

    std::vector<int> vs;
    for (std::size_t i = 0; i < 10e3; ++i) { // only 1000 elems in c++14 recursive method
        vs.emplace_back(i);
    }
    assert(array_view<int> {vs}.find(1000) == 1000);
    assert(array_view<int> {vs}.find(-1) == array_view<int>::npos);
}

int main() {
    static constexpr string_view strings[] = {
        "abcdddmmmnnncvnbcb",
        "aaa",
        "fff",
        "bbb",
        "ccc"
    };

    static_assert(strings[0].substr(0, 3) == strings[0].substr(0, 3), "");

    static_assert(string_view {strings[0].data(), 5}.size() == 5, "");
    static_assert(string_view {strings[0].substr(0, 3)}.size() == 3, "");
    static_assert(string_view {strings[0]}.size() == 18, "");
    static_assert(string_view {strings[1]}.size() == 3, "");
    static_assert(string_view {strings[0].substr(15)}.size() == 3, "");
    static_assert(string_view {strings[0].substr(15)} == "bcb", "");
    static_assert(string_view {strings[0].substr(0, 3)} == strings[0].substr(0, 3), "");
    static_assert(string_view {strings[0].substr(0, 3)} == string_view {"abc"}, "");

    static_assert(string_view {"ddd"} == string_view {"ddd"}, "");
    static_assert(string_view {"dda"} != string_view {"ddd"}, "");
    static_assert(string_view {"abc"} <  string_view {"aqq"}, "");
    static_assert(string_view {"Abc"} <  "abc", "");
    static_assert(string_view {"qbc"} == "qbc", "");
    static_assert(string_view {"abc"} <  string_view {"qwee"}, "");
    static_assert(string_view {"abc"} <  string_view {"qaa"}, "");
    static_assert(string_view {"abc"} >= string_view {"abb"}, "");
    static_assert(string_view {"qbc"} >= string_view {"qbc"}, "");
    static_assert(string_view {"qbc"} == string_view {"qbc"}, "");
    static_assert(string_view {"qbc"} >= string_view {"qbc"}, "");
    static_assert(string_view {"qbd"} >  string_view {"qbc"}, "");
    static_assert(string_view {"qbd"} >= string_view {"qbc"}, "");
    static_assert(string_view {"abc"} <= string_view {"qwee"}, "");
    static_assert(string_view {"abc"} <= string_view {"abc"}, "");

    static_assert(string_view {"Abc"}.at(1) == 'b', "");
    static_assert(string_view {"Abc"}[1] == 'b', "");

    static_assert(string_view {"HelloWorld"}.contains("HelloWorld"), "");
    static_assert(string_view {"HelloWorld"}.contains("Hello"), "");
    static_assert(string_view {"HelloWorld"}.contains("World"), "");
    static_assert(string_view {"HelloWorld"}.contains("ld"), "");
    static_assert(string_view {"Hello"}.contains("H"), "");
    static_assert(string_view {"Hello"}.contains(string_view{"H"}), "");
    static_assert(string_view {"Hello"}.contains("o"), "");
    static_assert(not string_view {"Hello"}.contains("z"), "");
    static_assert(not string_view {"HelloWorld"}.contains("Worlddddd"), "");
    static_assert(not string_view {"HelloWorld"}.contains("HelloWorld!"), "");
    static_assert(not string_view {"Hello"}.contains("HelloWorld"), "");
    static_assert(string_view {"o"}.in("Hello"), "");
    static_assert(string_view {"llo"}.in("Hello"), "");
    static_assert(string_view {'o'}.in("Hello"), "");

    static_assert(string_view {"Hello"}.find("Z") == string_view::npos, "");
    static_assert(string_view {"Hello"}.find("H") == 0, "");
    static_assert(string_view {"Hello"}.find("e") == 1, "");
    static_assert(string_view {"Hello"}.find("lo") == 3, "");
    static_assert(string_view {"Hello"}.find('o') == 4, "");
    static_assert(string_view {"Hello"}.find(string_view {"o"}) == 4, "");

    assert(string_view {"abc"} == std::string {"abc"});
    assert(std::string {"abc"} == string_view {"abc"});
    assert(not (string_view {"abc"} != std::string {"abc"}));
    assert(string_view {"Hello"}.contains(std::string{"H"}));
    assert(string_view {"o"}.in(std::string {"Hello"}));
    assert(not string_view {"o"}.in(std::string {"Hell"}));
    assert(string_view {"Hello"}.find(std::string {"o"}) == 4);

    const std::string stdstr {"hello"};
    const string_view str {stdstr};
    assert(str == "hello");
    assert(str.at(2) == 'l');

    assert(string_view {std::string {"my std string"}} == "my std string");

    constexpr string_view s {"Hello"};
    constexpr string_view s2 {s};

    std::cout << "s2 = " << s2 << std::endl;

    for (const auto& param : strings)
        std::cout << param << '\n';

    for (auto ch : strings[0]) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;

    std::cout << string_view {strings[0].substr(0, 3)} << '\n';

    main2();

    return 0;
}
