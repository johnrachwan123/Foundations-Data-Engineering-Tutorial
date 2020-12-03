#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>

#include "sum.hpp"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <lineitem.tbl>" << std::endl;
        return 1;
    }

    const auto start = high_resolution_clock::now();

    //-- exercise 3.4
    int handle = open(argv[1], O_RDONLY);
    lseek(handle, 0, SEEK_END);
    auto size = lseek(handle, 0, SEEK_CUR);
    // ensure that the mapping size is a multiple of 8 (bytes beyound the file's
    // region are set to zero)
    auto mapping_size = size + 8;  // padding for the last partition
    auto data = mmap(nullptr, size, PROT_READ, MAP_SHARED, handle, 0);
    //--
    int threads = std::stoi(argv[2]);
    int64_t price_sum = sum_parallel(data, size, threads);
    std::cout << price_sum << std::endl;

    const auto duration =
        duration_cast<milliseconds>(high_resolution_clock::now() - start)
            .count();
    std::cout << "duration: " << duration << " ms" << std::endl;

    //-- exercise 3.4
    // cleanup
    munmap(data, mapping_size);
    close(handle);
    //--

    return 0;
}
