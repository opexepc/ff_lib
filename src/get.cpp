//get.cpp
#include "../include/ff.h"

#pragma warning(push)
#pragma warning(disable : 4996)
std::string ff::get_home_path()
{
  #ifdef _WIN32
    const char* home_path = std::getenv("USERPROFILE");
  #else
    const char* home_path = std::getenv("HOME");
  #endif
  if(!home_path)
  {
    if(ff_logger)
      FF_LOG_ERR("get home path");
    return FF_NULL_STR;
  }
  else return std::string(home_path);
}
#pragma warning(pop)

std::string ff::get_config_path(const std::string &name_of_project)
{
  if(name_of_project.empty())
  {
    if(ff_logger)
      FF_LOG_ERR("name of project is empty");
    return FF_NULL_STR;
  }
  std::string after_home_path;
  #ifdef _WIN32
  after_home_path = "\\AppData\\local\\" + name_of_project + "\\";
  #else
  after_home_path = "/.config/" + name_of_project + "/";
  #endif
  return ff::get_home_path() + after_home_path;
}

int ff::get_str_count_stream(ff::stream &stream)
{
  switch(stream.mode)
  {
    case READ:
    {
      if(!stream.in_file)
      {
        if(ff_logger)
          FF_LOG_ERR("open file for read");
        return -1;
      }
      std::string line;
      int count = 1;
      stream.in_file.clear();
      stream.in_file.seekg(0);
      while(std::getline(stream.in_file, line)) count++;
      return count;
    }
    break;

    case WRITE:
      return stream.lines.size();
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
}

int ff::get_str_count(const std::string &path)
{
  ff::stream stream(path, READ);
  int count = ff::get_str_count_stream(stream);
  return count;
}