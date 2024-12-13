#include "interval_map.h"

int main() {
    // 1
    interval_map<int, int> imap_int;
    test_interval_map(imap_int, 1, 4, 6);
    test_interval_map(imap_int, 1, 3, 6);
    test_interval_map(imap_int, 1, 6, 9);
    test_interval_map(imap_int, 1, 1, 3);
    test_interval_map(imap_int, 2, 5, 10);
    test_interval_map(imap_int, 2, 8, 12);
    test_interval_map(imap_int, 3, 10, 15);

    // 2
    interval_map<int, float> imap_float;
    test_interval_map(imap_float, 1, 4.5f, 6.7f);
    test_interval_map(imap_float, 1, 3.1f, 6.7f);
    test_interval_map(imap_float, 1, 6.5f, 9.8f);
    test_interval_map(imap_float, 1, 1.0f, 3.1f);
    test_interval_map(imap_float, 2, 5.2f, 10.9f);
    test_interval_map(imap_float, 2, 8.1f, 12.3f);
    test_interval_map(imap_float, 3, 12.0f, 14.5f);

    // 3
    interval_map<std::string, int> imap_str_int;
    test_interval_map(imap_str_int, std::string("key1"), 4, 6);
    test_interval_map(imap_str_int, std::string("key1"), 3, 6);
    test_interval_map(imap_str_int, std::string("key2"), 1, 2);
    test_interval_map(imap_str_int, std::string("key3"), 5, 8);
    test_interval_map(imap_str_int, std::string("key1"), 2, 5);

    return 0;
}








