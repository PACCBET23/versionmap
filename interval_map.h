#ifndef INTERVAL_MAP_H
#define INTERVAL_MAP_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

template <typename K, typename V>
class interval_map {
public:
    void insert(const K& key, const V& start, const V& end);
    void print() const;

private:
    struct Interval {
        V first;
        V last;
        Interval(V f, V l);
        void print() const;
    };

    std::map<K, std::vector<Interval>> data;

    bool cross_intervals(const Interval& a, const Interval& b) const;
    typename interval_map<K, V>::Interval merge_intervals(const Interval& a, const Interval& b) const;
    void quick_sort(std::vector<Interval>& intervals, int left, int right);
    int partition(std::vector<Interval>& intervals, int left, int right);
};

template <typename K, typename V>
void test_interval_map(interval_map<K, V>& imap, const K& key, const V& start, const V& end) {
    imap.insert(key, start, end);
    imap.print();
}

template <typename K, typename V>
interval_map<K, V>::Interval::Interval(V f, V l) : first(f), last(l) {}

template <typename K, typename V>
void interval_map<K, V>::Interval::print() const {
    std::cout << "(" << first << "," << last << ")";
}

template <typename K, typename V>
void interval_map<K, V>::insert(const K& key, const V& start, const V& end) {
    Interval newInterval(start, end);
    auto& intervals = data[key];

    intervals.push_back(newInterval);
    quick_sort(intervals, 0, intervals.size() - 1);

    std::vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (cross_intervals(merged.back(), intervals[i])) {
            merged.back() = merge_intervals(merged.back(), intervals[i]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    intervals = std::move(merged);
}

template <typename K, typename V>
void interval_map<K, V>::print() const {
    for (const auto& [key, intervals] : data) {
        std::cout << key << ": ";
        for (const auto& interval : intervals) {
            interval.print();
            std::cout << "\n";
        }
    }
}

template <typename K, typename V>
bool interval_map<K, V>::cross_intervals(const Interval& a, const Interval& b) const {
    return a.last >= b.first && b.last >= a.first;
}

template <typename K, typename V>
typename interval_map<K, V>::Interval interval_map<K, V>::merge_intervals(const Interval& a, const Interval& b) const {
    return Interval(std::min(a.first, b.first), std::max(a.last, b.last));
}

template <typename K, typename V>
void interval_map<K, V>::quick_sort(std::vector<Interval>& intervals, int left, int right) {
    if (left >= right) return;

    int supIndex = partition(intervals, left, right);

    quick_sort(intervals, left, supIndex - 1);
    quick_sort(intervals, supIndex + 1, right);
}

template <typename K, typename V>
int interval_map<K, V>::partition(std::vector<Interval>& intervals, int left, int right) {
    Interval sup = intervals[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (intervals[j].first < sup.first) {
            ++i;
            std::swap(intervals[i], intervals[j]);
        }
    }

    std::swap(intervals[i + 1], intervals[right]);
    return i + 1;
}

#endif // INTERVAL_MAP_H

