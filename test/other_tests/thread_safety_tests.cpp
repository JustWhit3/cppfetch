#include <cppfetch/core.hpp>
#include <thread>

int main() {
    cppfetch::cppfetch downloader;
    auto job = [&downloader]() { downloader.download_single_file("https://arxiv.org/pdf/2207.01827.pdf"); };

    std::thread first_job(job);
    std::thread second_job(job);

    first_job.join();
    second_job.join();
}