#pragma GCC optimize ("O3")
#include <bits/stdc++.h>

template <class T, class U>
class Comparator {
    std::function<U (const T&)> _f;
    public:
        Comparator(const decltype(_f)& f) : _f(f) {}
        bool operator()(const T& u, const T& v) const noexcept { return _f(u) < _f(v); }
};

template <class T>
class SquareMatrix {
    size_t _n;
    std::vector<std::vector<T>> _mat;
    public:
        SquareMatrix(size_t n) : _n(n), _mat(n) { for (std::vector<T>& row : _mat) row.resize(n); }
        SquareMatrix(size_t n, T c) : SquareMatrix(n) { for (size_t i = 0; i < n; ++i) _mat[i][i] = c; }
        SquareMatrix<T>& operator*=(const SquareMatrix<T>&) noexcept;
        SquareMatrix<T>& operator+=(const SquareMatrix<T>&) noexcept;
        SquareMatrix<T> pow(size_t) noexcept;
        T sum(void) noexcept;
        inline T& operator()(size_t, size_t) noexcept;
        inline const T& operator()(size_t, size_t) const noexcept;
        inline size_t n(void) const noexcept { return _n; }
};

template <class T>
using Point = std::pair<T, T>;

template <class T>
constexpr T distance_squared(const Point<T>&, const Point<T>&) noexcept;

/**
 *  Code starts here
 */

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t m, n;
    std::cin >> m >> n;
    std::unordered_map<std::string, uint64_t> d;
    while (m--) {
        std::string s;
        uint64_t t;
        std::cin >> s >> t;
        d[s] = t;
    }
    while (n--) {
        std::string s;
        uint64_t t = 0;
        while (true) {
            std::cin >> s;
            if (s == ".") break;
            t += d[s];
        }
        std::cout << t << '\n';
    }
    return 0;
}

/**
 *  Code ends here
 */

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator*=(const SquareMatrix<T>& rhs) noexcept {
    if (_n != rhs.n()) {
        exit(-1);
    }
    SquareMatrix<T> buf(_n);
    for (size_t i = 0; i < _n; ++i) {
        for (size_t j = 0; j < _n; ++j) {
            for (size_t k = 0; k < _n; ++k) {
                buf(i, j) += this->operator()(i, k) * rhs(k, j);
            }
        }
    }
    return *this = buf;
}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator+=(const SquareMatrix<T>& rhs) noexcept {
    if (_n != rhs.n()) {
        exit(-1);
    }
    for (size_t i = 0; i < _n; ++i) {
        for (size_t j = 0; j < _n; ++j) {
            this->operator()(i, j) += rhs(i, j);
        }
    }
    return *this;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::pow(size_t p) noexcept {
    switch (p) {
        case 0:
            return SquareMatrix(_n, 1);
        case 1:
            return *this;
        default:
            auto m = pow(p / 2);
            m *= m;
            if (p % 2) {
                m *= *this;
            }
            return m;
    }
}

template <class T>
T SquareMatrix<T>::sum(void) noexcept {
    T x = 0;
    for (const std::vector<T>& row : _mat) {
        for (const T& cell : row) {
            x += cell;
        }
    }
    return x;
}

template <class T>
inline T& SquareMatrix<T>::operator()(size_t i, size_t j) noexcept {
    #ifdef DEBUG
    if (i > _n || j > _n) exit(-1);
    #endif
    return _mat[i][j];
}

template <class T>
inline const T& SquareMatrix<T>::operator()(size_t i, size_t j) const noexcept {
    #ifdef DEBUG
    if (i > _n || j > _n) exit(-1);
    #endif
    return _mat[i][j];
}

template <class T>
SquareMatrix<T> operator*(SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) noexcept {
    return lhs *= rhs;
}

template <class T>
SquareMatrix<T> operator+(SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) noexcept {
    return lhs += rhs;
}

template <class T>
constexpr T distance_squared(const Point<T>& u, const Point<T>& v) noexcept {
    T dx = u.first - v.first;
    T dy = u.second - v.second;
    return dx * dx + dy * dy;
}