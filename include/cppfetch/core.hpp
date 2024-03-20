// Progress bars o cose animate
// Tests
// Docstrings

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
            void download_single_file(const std::string& file_url,
                                      const std::filesystem::path& path_to_save = "") const;
            void add_file(const std::string& file);
            void download_all() const;

            // Getters
            const std::vector<std::string>& get_files_list() const;

            // Setters
            void set_verbose(bool flag);

        private:

            // Methods
            static size_t write_callback(void* contents, size_t size, size_t nmemb, std::filesystem::path* file_path);

            // Members
            std::vector<std::string> files_list;
            int16_t n_threads;
            bool verbose;
    };
}  // namespace cppfetch

#endif
