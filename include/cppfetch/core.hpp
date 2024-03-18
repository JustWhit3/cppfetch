#pragma once
#ifndef CPPFETCH_CORE_HPP
#define CPPFETCH_CORE_HPP

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace cppfetch {
    class cppfetch {
        public:

            // Constructors
            explicit cppfetch();

            // Methods
            void add_file(const std::string& file);
            void download_single_file(const std::string& file_url, const std::string& path_to_save);
            void download_all();

            // Getters
            const std::vector<std::string>& get_files_list();

        private:

            // Methods
            static size_t write_callback(void* contents, size_t size, size_t nmemb, std::filesystem::path* file_path);

            // Members
            std::vector<std::string> files_list;
            int16_t n_threads;
    };
}  // namespace cppfetch

#endif
