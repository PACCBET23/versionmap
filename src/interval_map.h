#ifndef INTERVAL_MAP_H
#define INTERVAL_MAP_H

#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

template<typename K, typename V>
class interval_map {
public:
    using Entry = std::pair<K, std::pair<V, V>>;

    void insert(const K& key, const std::pair<V, V>& new_interval);
    void print() const;

private:
    std::vector<Entry> data;

    bool intersects(const std::pair<V, V>& a, const std::pair<V, V>& b) const;

    std::pair<V, V> merge(const std::pair<V, V>& a, const std::pair<V, V>& b) const;

    struct Comparator;

    void quickSort(std::vector<Entry>& vec, int low, int high);
    int partition(std::vector<Entry>& vec, int low, int high);

    bool isValidInterval(const std::pair<V, V>& interval) const;
    bool isValidDigitInterval(const std::pair<V, V>& interval) const;
};

template<typename K, typename V>
void interval_map<K, V>::insert(const K& key, const std::pair<V, V>& new_interval) {
    if (!isValidInterval(new_interval) || !isValidDigitInterval(new_interval)) {
        return;
    }

    std::vector<Entry> merged_entries;
    bool merged = false;

    for (const auto& entry : data) {
        if (entry.first == key) {
            if (intersects(entry.second, new_interval)) {
                auto merged_interval = merge(entry.second, new_interval);
                if (!merged) {
                    merged_entries.push_back({key, merged_interval});
                    merged = true;
                }
            } else {
                merged_entries.push_back(entry);
            }
        } else {
            merged_entries.push_back(entry);
        }
    }

    if (!merged) {
        merged_entries.push_back({key, new_interval});
    }

    data = std::move(merged_entries);

    quickSort(data, 0, data.size() - 1);
}

template<typename K, typename V>
void interval_map<K, V>::print() const {
    if (data.empty()) {
        std::cout << "empty" << "\n";
        return;
    }
    K current_key = data.empty() ? K() : data[0].first;
    bool first_interval = true;

    for (const auto& entry : data) {
        if (entry.first != current_key) {
            std::cout << "\n";
            current_key = entry.first;
            first_interval = true;
        }
        if (!first_interval) {
            std::cout << ", ";
        }
        std::cout << "(" << entry.second.first << ", " << entry.second.second << ")";
        first_interval = false;
    }
    std::cout << "\n";
}

template<typename K, typename V>
bool interval_map<K, V>::intersects(const std::pair<V, V>& a, const std::pair<V, V>& b) const {
    return a.second >= b.first && b.second >= a.first;
}

template<typename K, typename V>
std::pair<V, V> interval_map<K, V>::merge(const std::pair<V, V>& a, const std::pair<V, V>& b) const {
    return {std::min(a.first, b.first), std::max(a.second, b.second)};
}

template<typename K, typename V>
struct interval_map<K, V>::Comparator {
    bool operator()(const Entry& a, const Entry& b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second.first < b.second.first;
    }
};

template<typename K, typename V>
void interval_map<K, V>::quickSort(std::vector<Entry>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);  //left
        quickSort(vec, pi + 1, high); //right
    }
}

template<typename K, typename V>
int interval_map<K, V>::partition(std::vector<Entry>& vec, int low, int high) {
    Entry pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (Comparator()(vec[j], pivot)) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

template<typename K, typename V>
bool interval_map<K, V>::isValidInterval(const std::pair<V, V>& interval) const {
    if (interval.first > interval.second) {
        std::cout << "incorrect interval: (" << interval.first << ", " << interval.second << ")" << "\n";
        return false;
    }
    return true;
}

template<typename K, typename V>
bool interval_map<K, V>::isValidDigitInterval(const std::pair<V, V>& interval) const {
    if constexpr (std::is_same_v<V, char>) {
        if (!std::isdigit(interval.first) || !std::isdigit(interval.second)) {
            std::cout << "incorrect interval: (" << interval.first << ", " << interval.second << ")" << "\n";
            return false;
        }
    } else if constexpr (std::is_same_v<V, std::string>) {
        for (const char& c : interval.first) {
            if (!std::isdigit(c)) {
                std::cout << "incorrect interval: (" << interval.first << ", " << interval.second << ")" << "\n";
                return false;
            }
        }
        for (const char& c : interval.second) {
            if (!std::isdigit(c)) {
                std::cout << "incorrect interval: (" << interval.first << ", " << interval.second << ")" << "\n";
                return false;
            }
        }
    }
    return true;
}

#endif
