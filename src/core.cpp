#include <omp.h>

#include <cppfetch/core.hpp>
#include <cstdint>
#include <iostream>
#include <string>

namespace cppfetch {
    // Constructors
    cppfetch::cppfetch() : n_threads(omp_get_num_procs()) {}

    // Getters
    const std::vector<std::string>& cppfetch::get_files_list() { return this->files_list; }

    // Methods
    void cppfetch::add_file(const std::string& file) { this->files_list.push_back(file); }

    void cppfetch::download_all() {
        omp_set_num_threads(n_threads);
        for (const auto& file: this->files_list) {
        }
    }
}  // namespace cppfetch