# CppProxyContainers
 c++17 string_view convenient analog for lightwieight strings and arrays proxies. 

Proxy containers do not allocate any memory. They hold pointer to existing container/string/vector/array/literal string.
String proxy can be used for convenient work with various string types. 
It has some usefull methods like in/contains/find which also do not allocate memory, but return you lightweight proxy to existing objects.
This containers can be used in generics functions called after creating real strings.
So you can be sure data is always const, and all operations on it does not lead to memory allocations.
All creations of std::string e.t.c will be perform explicit in code.

Examples:

```c++
// Strings
static constexpr const_string strings[] = {
    "abcdddmmmnnncvnbcb",
    "aaa",
    "fff",
    "bbb",
    "ccc"
};

static_assert(const_string {"ddd"} == const_string {"ddd"}, ""); // all other operators have been defined
static_assert(const_string {"Abc"}[1] == 'b', "");
static_assert(const_string {strings[0].substr(0, 3)} == const_string {"abc"}, "");
static_assert(const_string {strings[0].substr(15)}.size() == 3, "");
static_assert(const_string {"HelloWorld"}.contains("World"), "");
static_assert(const_string {"llo"}.in("Hello"), "");
static_assert(const_string {"Hello"}.find("lo") == 3, "");
static_assert(const_string {'o'}.in("Hello"), "");

assert(const_string {"abc"} == std::string {"abc"});
assert(const_string {"Hello"}.contains(std::string{"H"}));

// Arrays
constexpr std::array<int, 2> array1 {{1, 2}};
static_assert(const_array<int> {array1}.size() == 2, "");
static_assert(const_array<int> {array1} == array1, "");
static_assert(const_array<int> {array1}.contains(array1), "");
static_assert(const_array<int> {array1}.find(2) == 1, "");
static_assert(const_array<int> {array1}.find(3) == const_array<int>::npos, "");
static_assert(const_array<int> {1}.in(const_array<int> {array1}), "");

const std::vector<int> arr1 = {1, 2};
assert(const_array<int> {1}.in(arr1));

```
