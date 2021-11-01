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
        inline T& get(size_t, size_t) noexcept;
        inline const T& get(size_t, size_t) const noexcept;
        inline size_t n(void) const noexcept { return _n; }
};

/**
 *  Code starts here
 */

bool solve(size_t n, const std::vector<uint32_t>& v) {
    std::vector<uint32_t> r(n - 1);
    r[n - 2] = v[n - 1];
    for (size_t j = n - 3; j != -1; --j) {
        r[j] = std::max(r[j + 1], v[j + 1]);
    }
    std::set<uint32_t> s;
    s.insert(v[0]);
    for (size_t j = 1; j < n - 1; ++j) {
        auto it = s.upper_bound(v[j]);
        if (it != s.end() && *it < r[j]) return true;
        s.insert(v[j]);
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t k;
    std::cin >> k;
    std::vector<size_t> ans;
    for (size_t i = 1; i <= k; ++i) {
        size_t n;
        std::cin >> n;
        std::vector<uint32_t> v(n);
        for (uint32_t& x : v) std::cin >> x;
        if (solve(n, v)) ans.push_back(i);
    }
    std::cout << ans.size() << '\n';
    for (size_t x : ans) std::cout << x << '\n';
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
                buf.get(i, j) += get(i, k) * rhs.get(k, j);
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
            get(i, j) += rhs.get(i, j);
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
inline T& SquareMatrix<T>::get(size_t i, size_t j) noexcept {
    #ifdef DEBUG
    if (i > _n || j > _n) exit(-1);
    #endif
    return _mat[i][j];
}

template <class T>
inline const T& SquareMatrix<T>::get(size_t i, size_t j) const noexcept {
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