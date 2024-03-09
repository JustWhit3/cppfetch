#pragma once
#ifndef CPPFETCH_CORE_HPP
#define CPPFETCH_CORE_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace cppfetch {
    class cppfetch {
        public:

            // Constructors
            explicit cppfetch();

            // Methods
            void add_file(const std::string& file);
            void download_all();

            // Getters
            const std::vector<std::string>& get_files_list();

        private:

            std::vector<std::string> files_list;
            int16_t n_threads;
    };
}  // namespace cppfetch

#endif