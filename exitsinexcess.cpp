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
 *  [WA]
 */

struct G {
    size_t n, m;
    std::vector<std::vector<std::pair<size_t, size_t>>> g;
    std::vector<bool> ins;
    std::vector<bool> vis;
    std::vector<bool> del;
    std::vector<size_t> ans;
    G(size_t n, size_t m) : n(n), m(m), g(n), ins(n), vis(n), del(m) {}
};

void dfs(size_t x, G& g) {
    g.ins[x] = g.vis[x] = true;
    for (const auto& p : g.g[x]) {
        if (!g.del[p.second]) {
            if (g.vis[p.first]) {
                if (g.ins[p.first]) {
                    g.del[p.second] = true;
                    g.ans.push_back(p.second);
                }
            } else {
                dfs(p.first, g);
            }
        }
    }
    g.ins[x] = false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n, m;
    std::cin >> n >> m;
    G g(n, m);
    for (size_t i = 0; i < m; ++i) {
        size_t u, v;
        std::cin >> u >> v;
        g.g[--u].emplace_back(--v, i);
    }
    dfs(0, g);
    #ifdef DEBUG
    if (g.ans.size() > n / 2) exit(-1);
    #endif
    std::cout << g.ans.size() << '\n';
    for (size_t x : g.ans) std::cout << ++x << '\n';
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