#include <cppfetch/core.hpp>
#include <iostream>

int main() {
    // Initialize the downloader
    cppfetch::cppfetch downloader;
    downloader.set_verbose(true);

    // Add files to download
    downloader.add_file("https://arxiv.org/pdf/2207.01827.pdf");
    downloader.add_file("https://arxiv.org/ftp/arxiv/papers/2304/2304.13703.pdf");

    // Download all the files
    std::cout << "Parallelizing with " << downloader.get_n_threads() << " threads!\n";
    downloader.download_all();
}
