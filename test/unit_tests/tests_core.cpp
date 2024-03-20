#include <gtest/gtest.h>
#include <omp.h>

#include <cppfetch/core.hpp>
#include <filesystem>
#include <string>
#include <vector>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CoreTest, Constructors) {
    // Default constructor
    cppfetch::cppfetch downloader;
    ASSERT_FALSE(downloader.is_verbose());
    ASSERT_EQ(downloader.get_n_threads(), omp_get_num_procs());
}

TEST(CoreTest, Getters) {
    cppfetch::cppfetch downloader;

    // add_file & get_files_list
    ASSERT_TRUE(downloader.get_files_list().size() == 0);
    downloader.add_file("test");
    ASSERT_TRUE(downloader.get_files_list().size() == 1);
    EXPECT_EQ("test", downloader.get_files_list()[0]);

    // get_n_threads
    // ...
}

TEST(CoreTest, Setters) {
    cppfetch::cppfetch downloader;

    // set_verbose & is_verbose
    ASSERT_FALSE(downloader.is_verbose());
    downloader.set_verbose(true);
    ASSERT_TRUE(downloader.is_verbose());
}

TEST(CoreTest, download_single_file) {
    cppfetch::cppfetch downloader;
    std::filesystem::path path = std::filesystem::current_path() / "trash";
    std::filesystem::create_directory(path);

    // Case with standard name
    downloader.download_single_file("https://arxiv.org/pdf/2207.01827.pdf");
    ASSERT_TRUE(std::filesystem::exists("2207.01827.pdf"));
    ASSERT_TRUE(std::filesystem::is_regular_file("2207.01827.pdf"));

    // Case with different name
    downloader.download_single_file("https://arxiv.org/pdf/2207.01827.pdf", "trash/test.pdf");
    ASSERT_TRUE(std::filesystem::exists("trash/test.pdf"));
    ASSERT_TRUE(std::filesystem::is_regular_file("trash/test.pdf"));

    std::filesystem::remove("2207.01827.pdf");
    std::filesystem::remove("trash/test.pdf");
}

TEST(CoreTest, remove_file) {
    cppfetch::cppfetch downloader;
    downloader.add_file("test.txt");
    downloader.add_file("test_2.txt");
    downloader.remove_file("test.txt");
    std::vector<std::string> result = {"test_2.txt"};
    ASSERT_EQ(downloader.get_files_list(), result);
}