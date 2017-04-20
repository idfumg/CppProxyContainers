#ifndef PROXY_CONTAINERS_HPP
#define PROXY_CONTAINERS_HPP

#include <string>
#include <array>

namespace proxy_containers {

template<class T>
class const_array {
public:
    using const_iterator = const T* const;
    static constexpr auto npos = std::string::npos;

    constexpr const_array(const T* const pointer, const std::size_t N) noexcept
        : m_pointer {pointer}, m_size {N}
    {

    }

    template<std::size_t size>
    constexpr const_array(const std::array<T, size>& param) noexcept
        : const_array {&param[0], param.size()}
    {

    }

    template<class U>
    constexpr const_array(const U& param) noexcept
        : const_array {param.data(), param.size()}
    {

    }

    constexpr const_array(const T& param) noexcept
        : const_array {&param, 1}
    {

    }

    constexpr const T* data() const noexcept
    {
        return m_pointer;
    }

    constexpr std::size_t size() const noexcept
    {
        return m_size;
    }

    constexpr const_iterator begin() const noexcept
    {
        return m_pointer;
    }

    constexpr const_iterator end() const noexcept
    {
        return m_pointer + m_size;
    }

    constexpr const T& operator [] (const std::size_t i) const noexcept
    {
        return m_pointer[i];
    }

    constexpr const T& at (const std::size_t i) const noexcept
    {
        return m_pointer[i];
    }

    constexpr const_array subarray(const std::size_t pos, const std::size_t n) const noexcept
    {
        return const_array {data() + pos, n};
    }

    constexpr const_array subarray(const std::size_t pos) const noexcept
    {
        return substr(pos, size() - pos);
    }

    constexpr bool operator == (const const_array<T>& param) const noexcept
    {
        return isequal(m_pointer, 0, m_size, param.m_pointer, 0, param.size());
    }

    template<class U>
    constexpr bool operator == (const U& param) const noexcept
    {
        return isequal(m_pointer, 0, m_size, &param[0], 0, param.size());
    }

    template<class U>
    constexpr bool operator < (const U& param) const noexcept
    {
        return isless(m_pointer, 0, m_size, &param[0], 0, param.size());
    }

    template<class U>
    constexpr bool operator != (const U& param) const noexcept
    {
        return
            not operator==(param);
    }

    template<class U>
    constexpr bool operator > (const U& param) const noexcept
    {
        return
            not operator<(param) and
            not operator==(param);
    }

    template<class U>
    constexpr bool operator >= (const U& param) const noexcept
    {
        return
            not operator<(param);
    }

    template<class U>
    constexpr bool operator <= (const U& param) const noexcept
    {
        return
            operator<(param) or
            operator==(param);
    }

    template<class U>
    constexpr bool in(const U& param) const noexcept
    {
        return const_array<T> {param}.contains(*this);
    }

    constexpr bool contains(const T* const s, const std::size_t size) const noexcept
    {
        return size > m_size
            ? false
            : iscontains(s, 0, size, m_pointer, 0, m_size);
    }

    template<class U>
    constexpr bool contains(const U& param) const noexcept
    {
        return contains(&param[0], param.size());
    }

    constexpr std::size_t find(const T* const s, const std::size_t size) const noexcept
    {
        return find(s, 0, size, m_pointer, 0, m_size, 0);
    }

    template<class U>
    constexpr std::size_t find(const U& param) const noexcept
    {
        return find(param.data(), param.size());
    }

    constexpr std::size_t find(const T& param) const noexcept
    {
        return find(const_array<T> {&param, 1});
    }

protected:
    static constexpr bool isequal(
        const T* const a,
        const std::size_t acur,
        const std::size_t asize,
        const T* const b,
        const std::size_t bcur,
        const std::size_t bsize) noexcept
    {
#if __cplusplus < 201402L
        return (acur < asize and bcur < bsize)
            ? ((not (*a == *b))
               ? false
               : isequal(a + 1, acur + 1, asize, b + 1, bcur + 1, bsize))
            : asize == bsize;
#else
        if (asize != bsize) {
            return false;
        }

        for (std::size_t i = 0; i < asize; ++i) {
            if (a[i] != b[i]) {
                return false;
            }
        }

        return true;
#endif
    }

    static constexpr bool isless(
        const T* const a,
        const std::size_t acur,
        const std::size_t asize,
        const T* const b,
        const std::size_t bcur,
        const std::size_t bsize) noexcept
    {
#if __cplusplus < 201402L
        return ((acur < asize and bcur < bsize)
            ? ((*a < *b)
               ? true
               : ((*a == *b)
                  ? isless(a + 1, acur + 1, asize, b + 1, bcur + 1, bsize)
                  : false))
            : (asize < bsize));
#else
        if (asize > bsize) {
            return false;
        }

        const std::size_t minsize = asize < bsize ? asize : bsize;
        for (std::size_t i = 0; i < minsize; ++i) {
            if (a[i] < b[i]) {
                return true;
            }
            else if (a[i] == b[i]) {
                continue;
            }
            else {
                return false;
            }
        }

        return asize < bsize;
#endif
    }

#if __cplusplus < 201402L
    static constexpr bool iscontains_helper(
        const T* const a,
        const std::size_t acur,
        const std::size_t asize,
        const T* const b,
        const std::size_t bcur,
        const std::size_t bsize) noexcept
    {
        return ((acur < asize and bcur < bsize)
                ? (*a == *b and iscontains_helper(a+1, acur+1, asize, b+1, bcur+1, bsize))
                : (acur >= asize ));
    }
#endif

    static constexpr bool iscontains(
        const T* const a,
        const std::size_t acur,
        const std::size_t asize,
        const T* const b,
        const std::size_t bcur,
        const std::size_t bsize) noexcept
    {
#if __cplusplus < 201402L
        return iscontains_helper(a, acur, asize, b, bcur, bsize) or
            ((bsize - bcur >= asize - acur) and
             iscontains(a, acur, asize, b + 1, bcur + 1, bsize));
#else
        std::size_t i = 0;
        while (i < bsize and (bsize - i >= asize)) {
            if (const_array {b + i, asize} == const_array {a, asize}) {
                return true;
            }
            i++;
        }
        return false;
#endif
    }

    static constexpr std::size_t find(
        const T* const a,
        const std::size_t acur,
        const std::size_t asize,
        const T* const b,
        const std::size_t bcur,
        const std::size_t bsize,
        const std::size_t found) noexcept
    {
#if __cplusplus < 201402L
        return iscontains_helper(a, acur, asize, b, bcur, bsize)
            ? found
            : ((bsize - bcur >= asize - acur)
               ? find(a, acur, asize, b + 1, bcur + 1, bsize, found + 1)
               : npos);
#else
        std::size_t i = 0;
        while (i < bsize and (bsize - i >= asize)) {
            if (const_array {b + i, asize} == const_array {a, asize}) {
                return i;
            }
            i++;
        }
        return npos;
#endif
    }

private:
    const T* const m_pointer {nullptr};
    const std::size_t m_size;
};

template <class StreamT, class T>
inline StreamT& operator << (StreamT& stream, const const_array<T>& param) noexcept
{
    stream << '[';
    for (std::size_t i = 0; i < param.size(); ++i) {
        stream << param[i];
        if (i + 1 != param.size()) {
            stream << ", ";
        }
    }
    stream << ']';
    return stream;
}

template<class ContainerT, class T>
constexpr bool operator == (const ContainerT& container, const const_array<T>& arr) noexcept
{
    return arr == container;
}


class const_string : public const_array<char> {
public:
    using const_array<char>::const_array;
    using const_array<char>::operator<;
    using const_array<char>::operator<=;
    using const_array<char>::operator==;
    using const_array<char>::operator>;
    using const_array<char>::operator>=;
    using const_array<char>::contains;
    using const_array<char>::in;
    using const_array<char>::find;

    template <std::size_t N>
    constexpr const_string(const char(&pointer)[N]) noexcept
        : const_array {pointer, N - 1}
    {

    }

    constexpr const const_string substr(const std::size_t pos, const std::size_t n) const noexcept
    {
        return const_array<char>::subarray(pos, n);
    }

    constexpr const const_string substr(const std::size_t pos) const noexcept
    {
        return const_array<char>::subarray(pos, size() - pos);
    }

    template<std::size_t N>
    constexpr bool operator == (const char(&s)[N]) const noexcept
    {
        return isequal(data(), 0, size(), s, 0, N - 1);
    }

    template<std::size_t N>
    constexpr bool operator < (const char(&s)[N]) const noexcept
    {
        return isless(data(), 0, size(), s, 0, N - 1);
    }

    template<std::size_t N>
    constexpr bool in(const char(&s)[N]) const noexcept
    {
        return const_string {s, N - 1}.contains(*this);
    }

    template<std::size_t N>
    constexpr bool contains(const char(&s)[N]) const noexcept
    {
        return contains(s, N - 1);
    }

    template<std::size_t N>
    constexpr std::size_t find(const char(&s)[N]) const noexcept
    {
        return find(s, N - 1);
    }
};

template <class StreamT>
inline StreamT& operator << (StreamT& stream, const const_string& param) noexcept
{
    stream << '\'';
    stream.write(param.data(), param.size());
    stream << '\'';
    return stream;
}

template<class T>
constexpr bool operator == (const std::string& container, const const_string& arr) noexcept
{
    return arr == container;
}

} /* namespace proxy_containers */

#endif /* PROXY_CONTAINERS_HPP */
