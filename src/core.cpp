#include <curl/curl.h>
#include <omp.h>

#include <cppfetch/core.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cppfetch {
    // Constructors
    cppfetch::cppfetch() : n_threads(omp_get_num_procs()) {}

    // Getters
    const std::vector<std::string>& cppfetch::get_files_list() { return this->files_list; }

    // Methods
    void cppfetch::add_file(const std::string& file) { this->files_list.push_back(file); }

    size_t cppfetch::write_callback(void* contents, size_t size, size_t nmemb, std::filesystem::path* file_path) {
        std::ofstream file(*file_path, std::ios::out | std::ios::app | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << file_path->string() << "\n";
        }
        size_t totalSize = size * nmemb;
        file.write(reinterpret_cast<const char*>(contents), totalSize);
        file.close();
        return totalSize;
    }

    void cppfetch::download_single_file(const std::string& file_url, const std::string& path_to_save) {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL* curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, file_url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &path_to_save);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Error while downloading: " << curl_easy_strerror(res) << "\n";
            }
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Cannot initialize libcurl!"
                      << "\n";
        }
    }

    void cppfetch::download_all() {
        // omp_set_num_threads(n_threads);
        for (const auto& file: this->files_list) {
        }
    }
}  // namespace cppfetch
