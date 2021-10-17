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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t k;
    std::cin >> k;
    while (k--) {
        size_t n;
        std::cin >> n;
        uint32_t s = 1, t = n;
        while (n--) {
            uint32_t x;
            std::cin >> x;
            if (x == s) {
                ++s;
                --t;
            }
        }
        std::cout << t << '\n';
    }
    return 0;
}