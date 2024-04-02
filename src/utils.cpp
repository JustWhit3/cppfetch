#include <cppfetch/utils.hpp>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cppfetch {
    /**
     * @brief Callback function for writing downloaded data to file.
     *
     * @param contents Pointer to the data.
     * @param size Size of each element.
     * @param nmemb Number of elements.
     * @param file_path Pointer to the file path where data is to be written.
     * @return Total size of data written.
     */
    size_t write_callback(void* contents, size_t size, size_t nmemb, std::filesystem::path* file_path) {
        std::ofstream file(*file_path, std::ios::out | std::ios::app | std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << file_path->string() << "\n";
            std::exit(0);
        }

        size_t totalSize = size * nmemb;
        file.write(reinterpret_cast<const char*>(contents), totalSize);

        if (!file.good()) {
            std::cerr << "Error writing to file\n";
            std::exit(0);
        }

        file.close();
        return totalSize;
    }
}  // namespace cppfetch