# CppProxyContainers
 c++11 convenient analog of c++17 string_view for lightwieight strings and arrays proxies.

Proxy containers do not allocate any memory. They hold pointer to existing container/string/vector/array/literal string.
String proxy can be used for convenient work with various string types.
It has some usefull methods like in/contains/find which also do not allocate memory, but return you lightweight proxy to existing objects.
This containers can be used in generics functions called after creating real strings.
So you can be sure data is always const, and all operations on it does not lead to memory allocations.
All creations of std::string e.t.c will be perform explicit in code.

Examples:

```c++
// Strings
static constexpr string_view strings[] = {
    "abcdddmmmnnncvnbcb",
    "aaa",
    "fff",
    "bbb",
    "ccc"
};

static_assert(string_view {strings[0].substr(15)} == "bcb", "");
static_assert(string_view {"ddd"} == string_view {"ddd"}, ""); // all other operators have been defined
static_assert(string_view {"Abc"}[1] == 'b', "");
static_assert(string_view {strings[0].substr(0, 3)} == string_view {"abc"}, "");
static_assert(string_view {strings[0].substr(15)}.size() == 3, "");
static_assert(string_view {"HelloWorld"}.contains("World"), "");
static_assert(string_view {"llo"}.in("Hello"), "");
static_assert(string_view {"Hello"}.find("lo") == 3, "");
static_assert(string_view {'o'}.in("Hello"), "");

assert(string_view {"abc"} == std::string {"abc"});
assert(string_view {"Hello"}.contains(std::string{"H"}));

// Arrays
constexpr std::array<int, 3> array3 {{1, 2, 3}};
static_assert(array_view<int> {array3}[2] == 3, "");
// to create a array_view of several elements we need allocate contiguos chunk of memory, so impossible to implement
static_assert(array_view<int> {array3}.subarray(2) == array_view<int> {3}, "");

constexpr std::array<int, 2> array1 {{1, 2}};
static_assert(array_view<int> {array1}.size() == 2, "");
static_assert(array_view<int> {array1} == array1, "");
static_assert(array_view<int> {array1}.contains(array1), "");
static_assert(array_view<int> {array1}.find(2) == 1, "");
static_assert(array_view<int> {array1}.find(3) == array_view<int>::npos, "");
static_assert(array_view<int> {1}.in(array_view<int> {array1}), "");

const std::vector<int> arr1 = {1, 2};
assert(array_view<int> {1}.in(arr1));

```
