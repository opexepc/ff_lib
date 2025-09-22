//copy.cpp
#include "../include/ff.h"

bool ff::copy(const std::string &from_path, const std::string &to_path)
{
  std::filesystem::copy(from_path, to_path, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
  return true;
}