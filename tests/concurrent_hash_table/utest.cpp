#include "mu_test.h"
#include "threads_concurrent_hash_table.hpp"

#include <string>
#include <thread>
#include <vector>
#include <algorithm>

BEGIN_TEST(check_insert_erase)
    using namespace threads;

    ConcurrentHashTable<int, int> hash;

    std::pair<size_t, size_t> range1 {0, 10'000};
    std::pair<size_t, size_t> range2 {10'000, 20'000};

    std::thread thread1([&hash, range1](){
        for (size_t i = range1.first; i < range1.second; ++i) {
                hash.Insert(i, i);
        }
    });

    std::thread thread2([&hash, range2](){
        for (size_t i = range2.first; i < range2.second; ++i) {
                hash.Insert(i, i);
        }
    });

    std::vector<size_t> earsedElements;
    std::pair<size_t, size_t> rangeEarse {5'000, 15'000};

    std::thread thread3([&hash, &earsedElements, rangeEarse](){
        for (size_t i = rangeEarse.first; i < rangeEarse.second; ++i) {
            if(hash.Erase(i)) {
                earsedElements.push_back(i);
            }
        }
    });

    thread1.join();
    thread2.join();
    thread3.join();

    for(size_t i = range1.first; i < range2.second; ++i) {
        if(std::find(earsedElements.begin(), earsedElements.end(), i) != earsedElements.end()) {
            std::cout << "earsed " << i << '\n';
            ASSERT_EQUAL(hash.Containes(i), false);
        }
        else {
            std::cout << "not earsed " << i << '\n';
            ASSERT_EQUAL(hash.Containes(i), true);
        }
    }
END_TEST


BEGIN_SUITE(Its what you learn after you know it all that counts)
	TEST(check_insert_erase)
END_SUITE
