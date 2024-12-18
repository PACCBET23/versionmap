#include "interval_map.h"

void test_interval_map() {//пример из условия
    interval_map<int, int> map;

    map.insert(1, {4, 6});
    map.insert(1, {3, 6});
    map.insert(1, {6, 9});
    map.insert(1, {1, 3});

    map.print();
}

void test_interval_map2() {//пример из условия 2
    interval_map<int, int> map;

    //map.insert(1, {4, 6});
    //map.insert(1, {3, 6});
    map.insert(1, {6, 9});
    map.insert(1, {1, 3});

    map.print();
}

void test_interval_map3() {//пример из условия 3
    interval_map<int, int> map;

    map.insert(1, {4, 6});
    map.insert(1, {3, 6});
    //map.insert(1, {6, 9});
    //map.insert(1, {1, 3});

    map.print();
}

void test_interval_map4() {//несколько интервалов с разными ключами
    interval_map<int, int> map;

    map.insert(1, {1, 5});
    map.insert(2, {3, 7});
    map.insert(3, {6, 9});

    map.print();
}

void test_interval_map5() {//пустой ввод
    interval_map<int, int> map;

    map.print();
}

void test_interval_map6() {//интервалы с нулевой длиной
    interval_map<int, int> map;

    map.insert(1, {5, 5});
    map.insert(1, {3, 3});
    map.insert(1, {7, 7});

    map.print();
}

void test_interval_map7() {//интервалы с разными типами
    interval_map<int, char> map;

    map.insert(1, {'a', 'd'});
    map.insert(1, {'1', '3'});
    map.insert(2, {'f', 'i'});

    map.print();
}

void test_interval_map8() {//некорректные интервалы
    interval_map<int, int> map;

    map.insert(1, {5, 3});
    map.insert(1, {7, 10});
    map.insert(1, {12, 8});

    map.print();
}


int main() {
    test_interval_map();
    test_interval_map2();
    test_interval_map3();
    test_interval_map4();
    test_interval_map5();
    test_interval_map6();
    test_interval_map7();
    test_interval_map8();

    return 0;
}









