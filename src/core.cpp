#include <curl/curl.h>
#include <omp.h>

#include <algorithm>
#include <cppfetch/core.hpp>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace cppfetch {
    /**
     * @brief Default constructor for cppfetch class.
     */
    cppfetch::cppfetch() : n_threads(omp_get_num_procs()), verbose(false) {}

    /**
     * @brief Get the list of files to be fetched.
     *
     * @return Reference to the vector containing the list of files.
     */
    const std::vector<std::string>& cppfetch::get_files_list() const { return this->files_list; }

    /**
     * @brief Get the number of threads used for fetching files in parallel.
     *
     * @return Number of threads.
     */
    int16_t cppfetch::get_n_threads() const { return this->n_threads; }

    /**
     * @brief Set verbose mode.
     *
     * @param flag Boolean flag indicating whether to enable verbose mode.
     */
    void cppfetch::set_verbose(bool flag) { this->verbose = flag; }

    /**
     * @brief Add a file to the list of files to be fetched.
     *
     * @param file Path of the file to be added.
     */
    void cppfetch::add_file(const std::string& file) { this->files_list.push_back(file); }

    /**
     * @brief Remove a file from the list of files to be fetched.
     *
     * @param file Path of the file to be removed.
     */
    void cppfetch::remove_file(const std::string& file) {
        auto it = std::find(this->files_list.begin(), this->files_list.end(), file);
        if (it != this->files_list.end()) {
            this->files_list.erase(it);
        } else {
            std::cerr << "File \"" << file << "\" has not been added to the list of files to be downloaded!\n";
        }
    }

    /**
     * @brief Callback function for writing downloaded data to file.
     *
     * @param contents Pointer to the data.
     * @param size Size of each element.
     * @param nmemb Number of elements.
     * @param file_path Pointer to the file path where data is to be written.
     * @return Total size of data written.
     */
    size_t cppfetch::write_callback(void* contents, size_t size, size_t nmemb, std::filesystem::path* file_path) {
        std::ofstream file(*file_path, std::ios::out | std::ios::app | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << file_path->string() << "\n";
            std::exit(0);
        }
        size_t totalSize = size * nmemb;
        file.write(reinterpret_cast<const char*>(contents), totalSize);
        file.close();
        return totalSize;
    }

    /**
     * @brief Download a single file from a given URL and save it to a specified path.
     *
     * @param file_url URL of the file to be downloaded.
     * @param path_to_save Optional. Path where the file is saved. If not provided, the file is saved in the current
     * directory with a default name produced starting from the URL name.
     */
    void cppfetch::download_single_file(const std::string& file_url, const std::filesystem::path& path_to_save) const {
        if (this->verbose) {
#pragma omp critical
            { std::cout << "Downloading file: " << file_url << "...\n"; }
        }

        curl_global_init(CURL_GLOBAL_ALL);
        CURL* curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, file_url.c_str());

            // Choose standard file name if path is empty
            std::filesystem::path actual_path_to_save = path_to_save;
            if (actual_path_to_save.empty()) {
                std::string filename;
                size_t last_slash = file_url.find_last_of('/');
                if (last_slash != std::string::npos) {
                    filename = file_url.substr(last_slash + 1);
                } else {
                    filename = "downloaded_file";
                }
                actual_path_to_save = filename;
            }

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &actual_path_to_save);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "\nError while downloading: " << curl_easy_strerror(res) << "\n";
                std::exit(0);
            }
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Cannot initialize libcurl!"
                      << "\n";
            std::exit(0);
        }
    }

    /**
     * @brief Check if verbose mode is enabled.
     *
     * @return True if verbose mode is enabled, false otherwise.
     */
    bool cppfetch::is_verbose() const { return this->verbose; }

    // TODO: docstring
    // TODO: set num threads omp_set_num_threads(n_threads);
    // TODO: progress bars
    // TODO: choose if parallelize or not
    void cppfetch::download_all(const std::filesystem::path& path_to_save, bool parallelize) const {
        if (parallelize) {
#pragma omp parallel for
            for (const auto& file: this->files_list) {
                this->download_single_file(file, path_to_save);
            }
        } else {
            for (const auto& file: this->files_list) {
                this->download_single_file(file, path_to_save);
            }
        }
    }
}  // namespace cppfetch
