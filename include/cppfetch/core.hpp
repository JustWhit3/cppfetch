// Thread safety

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

            // Getters
            const std::vector<std::string>& get_files_list() const;
            int16_t get_n_threads() const;

            // Setters
            void set_verbose(bool flag);

            // Methods
            void download_single_file(const std::string& file_url,
                                      const std::filesystem::path& path_to_save = "") const;
            void add_file(const std::string& file);
            bool is_verbose() const;
            void remove_file(const std::string& file);
            void download_all(const std::filesystem::path& path_to_save = "", bool parallelize = true) const;

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
