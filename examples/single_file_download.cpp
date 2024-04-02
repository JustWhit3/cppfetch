#include <cppfetch/core.hpp>

int main() {
    // Initialize the downloader
    cppfetch::cppfetch downloader;
    downloader.set_verbose(true);

    // Download single file
    downloader.download_single_file("https://arxiv.org/pdf/2207.01827.pdf");
}
