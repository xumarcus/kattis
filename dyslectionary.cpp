#pragma GCC optimize ("O3")

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

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
    std::vector<std::string> v;
    const Comparator<std::string, size_t> comp([](const auto& t) { return t.length(); });
    while (!std::cin.eof()) {
        std::string s;
        std::getline(std::cin, s);
        if (s.empty()) {
            const size_t width = std::max_element(v.begin(), v.end(), comp)->length();
            for (std::string& t : v) {
                std::reverse(t.begin(), t.end());
            }
            std::sort(v.begin(), v.end());
            for (std::string& t : v) {
                std::reverse(t.begin(), t.end());
                std::cout << std::right << std::setw(width) << t << '\n';
            }
            if (std::char_traits<char>::not_eof(std::cin.peek())) {
                std::cout << '\n';
            }
            v.clear();
        } else {
            v.push_back(std::move(s));
        }
    }
}