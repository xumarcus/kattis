#pragma GCC optimize ("O3")
#include <bits/stdc++.h>

template <class T>
using Point = std::pair<T, T>;

template <class T>
constexpr T distance_squared(const Point<T>&, const Point<T>&) noexcept;

template <class T>
using PQueue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n;
    std::cin >> n;
    std::vector<std::pair<int64_t, int64_t>> ps(n + 2);
    for (auto& p : ps) {
        std::cin >> p.first >> p.second;
    } 
    std::vector<size_t> rev(n + 2, -1);
    std::vector<int64_t> dist(n + 2, std::numeric_limits<int64_t>::max());
    std::vector<bool> vis(n + 2);
    dist[n] = 0;
    while (true) {
        size_t t = -1;
        for (size_t i = 0; i < n + 2; ++i) {
            if (!vis[i] && (t == -1 || dist[i] < dist[t])) t = i;
        }
        if (t == -1) break;
        vis[t] = true;
        for (size_t i = 0; i < n + 2; ++i) {
            if (vis[i]) continue;
            int64_t z = dist[t] + distance_squared(ps[t], ps[i]);
            if (z < dist[i]) {
                dist[i] = z;
                rev[i] = t;
            }
        }
    }
    std::vector<size_t> path;
    for (size_t i = n + 1; rev[i] != n; i = rev[i]) {
        #ifdef DEBUG
        if (rev[i] == -1) exit(-1);
        #endif
        path.push_back(rev[i]);
    }
    if (path.empty()) {
        std::cout << "-\n";
    } else {
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << *it << '\n';
        }
    }
    return 0;
}

template <class T>
constexpr T distance_squared(const Point<T>& u, const Point<T>& v) noexcept {
    T dx = u.first - v.first;
    T dy = u.second - v.second;
    return dx * dx + dy * dy;
}