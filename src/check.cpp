//check.cpp
#include "../include/ff.h"

bool ff::file_exists(const std::string& path)
{
  return
    std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
}

bool dir_exists(const std::string &path)
{
  return
    std::filesystem::exists(path) && std::filesystem::is_directory(path);;
}