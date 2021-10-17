#pragma GCC optimize ("O3")
#include <bits/stdc++.h>

template <class T, class U>
class Comparator {
    using F = std::function<U (const T&)>;
    F _f;
    public:
        Comparator(const F& f) : _f(f) {}
        bool operator()(const T& u, const T& v) const noexcept {
            return _f(u) < _f(v);
        }
};

template <class T>
class SquareMatrix {
    size_t _n;
    std::vector<std::vector<T>> _mat;
    public:
        SquareMatrix(size_t n) : _n(n), _mat(n) {
            for (std::vector<T>& row : _mat) {
                row.resize(n);
            }
        }
        SquareMatrix<T>& operator*=(const SquareMatrix<T>& rhs) {
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

        T& get(size_t i, size_t j) {
            return _mat[i][j];
        }
        const T& get(size_t i, size_t j) const {
            return _mat[i][j];
        }
        size_t n(void) const {
            return _n;
        }
};

template <class T>
SquareMatrix<T> operator*(SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) {
    return lhs *= rhs;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n, m;
    std::cin >> n >> m;
    std::vector<size_t> d(n);
    SquareMatrix<double> s(n);
    while (m--) {
        size_t i, j;
        std::cin >> i >> j;
        s.get(i, j) = 1.0;
        s.get(j, i) = 1.0;
        ++d[i];
        ++d[j];
    }
    for (size_t i = 0; i < n - 1; ++i) {
        if (!d[i]) {
            exit(-1);
        }
        for (size_t j = 0; j < n - 1; ++j) {
            s.get(i, j) /= static_cast<double>(d[i]);
        }
        s.get(i, n - 1) = 1.0;
    }
    for (size_t j = 0; j < n - 1; ++j) {
        s.get(n - 1, j) = 0.0;
    }
    s.get(n - 1, n - 1) = 1.0;
    for (size_t i = 0; i < 1000; ++i) {
        s *= s;
    }
    std::cout << std::setprecision(6) << std::fixed << s.get(0, n - 1) << '\n';
    return 0;
}