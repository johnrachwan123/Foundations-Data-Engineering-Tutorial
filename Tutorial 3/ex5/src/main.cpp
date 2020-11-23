#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

#include "sum.hpp"

using namespace std::chrono;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <lineitem.tbl>" << std::endl;
        return 1;
    }

    const auto start = high_resolution_clock::now();

    //-- TODO exercise 3.4
    // your code goes here
    //--

    int handle = open(argv[1], O_RDONLY);
    auto size = lseek(handle, 0, SEEK_END);
    auto mapping_size = size + 8;
    auto data = mmap(nullptr, mapping_size, PROT_READ, MAP_SHARED, handle, 0);

    char *data_start = static_cast<char *>(data);
    int64_t price_sum;
    sum_extendedprice<true>(data_start, data_start, size, &price_sum);
    std::cout << price_sum << std::endl;

    const auto duration =
            duration_cast<milliseconds>(high_resolution_clock::now() - start)
                    .count();
    std::cout << "duration: " << duration << " ms" << std::endl;

    //-- TODO exercise 3.4
    // cleanup
    //--
    munmap(data, mapping_size);
    close(handle);
    return 0;
}
