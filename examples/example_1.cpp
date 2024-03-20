#include <cppfetch/core.hpp>
#include <iostream>

int main() {
    // Initialize the downloader
    cppfetch::cppfetch downloader;
    downloader.set_verbose(true);

    // Download single file
    downloader.download_single_file("https://root.cern/download/root_v6.30.04.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz");

    // Add files to download
    // downloader.add_file("my_file.txt");
    // downloader.add_file("another_file.txt");

    // Print chosen files names
    // auto files_list = downloader.get_files_list();
    // for (const auto& file: files_list) {
    //     std::cout << file << "\n";
    // }

    // Download all the files
    // downloader.download_all();
}
