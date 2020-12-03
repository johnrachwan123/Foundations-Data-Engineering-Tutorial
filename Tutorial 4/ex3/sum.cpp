#include <cassert>
#include <memory>
#include <numeric>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include "sum.hpp"

int64_t ToInt(std::string_view s) {
    int64_t result = 0;
    for (auto c : s) result = result * 10 + (c - '0');
    return result;
}

// pattern : the character to search broadcasted into a 64-bit integer
// block : memory block in which to search
// return : 64-bit integer with all the matches as seen in the lecture
inline uint64_t get_matches(uint64_t pattern, uint64_t block) {
    //-- exercise 3.4 part 2
    constexpr uint64_t high = 0x8080808080808080ull;
    constexpr uint64_t low = 0x7F7F7F7F7F7F7F7Full;
    uint64_t lowChars = (~block) & high;
    uint64_t foundChars = ~((((block & low) ^ pattern) + low) & high);
    uint64_t matches = foundChars & lowChars;
    return matches;
    //--
}

// pattern : the character to search broadcasted into a 64bit integer
// begin : points somewhere into the partition
// len : remaining length of the partition
// return : the position of the first matching character or -1 otherwise
ssize_t find_first(uint64_t pattern, const char *begin, size_t len) {
    // locate the position of the following character (you'll have to use the
    // pattern argument directly in the second part of the exercise)
    const char to_search = pattern & 0xff;

    // Hint: You may assume that reads from 'begin' within [len, len + 8) yield
    // zero
    //-- exercise 3.4
    size_t i = 0;
    while (i < len) {
        uint64_t block = *reinterpret_cast<const uint64_t *>(begin + i);
        uint64_t matches = get_matches(pattern, block);
        if (matches != 0) {
            uint64_t pos = __builtin_ctzll(matches) / 8;
            if (pos < 8) {
                return (i + pos);
            }
        }
        i += 8;
    }
    //--
    return -1;
}

// begin : points somewhere into the partition
// len : remaining length of the partition
// return : 64-bit integer representation of the provided numeric
int64_t read_numeric(const char *begin, size_t len) {
    constexpr uint64_t period_pattern = 0x2E2E2E2E2E2E2E2Eull;
    std::string_view numeric_view(begin, len);
    ssize_t dot_position = find_first(period_pattern, begin, len);
    assert(dot_position > 0);
    auto part1 = numeric_view.substr(0, dot_position);
    auto part2 = numeric_view.substr(dot_position + 1);
    int64_t numeric = ToInt(part1) * 100 + ToInt(part2);
    return numeric;
}

static std::vector<int64_t> results;

// data : pointer to the first byte of the file
// size : dataset size in bytes
// return : 64-bit integer result
int64_t sum_parallel(const void *data, size_t size, int num_threads) {
//    const size_t num_threads = std::thread::hardware_concurrency();
    results.resize(num_threads, 0);
    std::thread threads[num_threads];

    size_t remaining = size;
    size_t partition_size = size / num_threads;
    const char *data_start = static_cast<const char *>(data);
    const char *partion_start = data_start;
    //-- TODO exercise 4.3
    // your code goes here
    for (size_t i = 0; i < num_threads; i++) {
        size_t size_hint = std::min(remaining, partition_size);
        remaining -= size_hint;
        int64_t *result = &results[i];
        if(i == 0) {
            threads[0] = std::thread(sum_extendedprice<true>,
                    data_start, partion_start, size_hint, result);
        } else {
            threads[i] = std::thread(sum_extendedprice<false>,
                                     data_start, partion_start, size_hint, result);
        }
        partion_start +=size_hint;
    }

    for (size_t i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    //--

    // aggregate results of all workers
    int64_t price_sum = std::accumulate(results.begin(), results.end(), 0ul);
    return price_sum;
}
