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
        SquareMatrix<T>& operator*=(const SquareMatrix<T>&);
        T& get(size_t i, size_t j) { return _mat[i][j]; }
        const T& get(size_t i, size_t j) const { return _mat[i][j]; }
        size_t n(void) const noexcept { return _n; }
};

/**
 *  Code starts here
 */

const size_t N = 1000 + 1;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::bitset<N>> bss(n);
    for (std::bitset<N>& bs : bss) {
        size_t k;
        std::cin >> k;
        while (k--) {
            size_t l;
            std::cin >> l;
            bs.set(l);
        }
    }
    uint32_t ans = 0;
    std::bitset<N> t;
    while (m--) {
        size_t x;
        std::cin >> x;
        t.set(x);
        if (std::all_of(bss.begin(), bss.end(), [&](const std::bitset<N>& bs) {
            return (t & bs) != t;
        })) {
            ++ans;
            t.reset();
            t.set(x);
        }
    }
    std::cout << ans << '\n';
    return 0;
}

/**
 *  Code ends here
 */

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator*=(const SquareMatrix<T>& rhs) {
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
SquareMatrix<T> operator*(SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) {
    return lhs *= rhs;
}