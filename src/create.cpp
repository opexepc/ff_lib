//create.cpp
#include "../include/ff.h"

bool ff::create_file(const std::string &path, bool del)
{
  if(del)
    std::remove(path.c_str());
  std::ifstream in_file(path);
  if(!in_file)
  {
    std::ofstream out_file(path);
    if(!out_file)
    {
      if(ff_logger)
        FF_LOG_ERR("create file");
      return false;
    }
    else
    {
      out_file.close();
      return true;
    }
  }
  else
  {
    in_file.close();
    return false;
  }
}

bool ff::create_dir(const std::string &path, bool del)
{
  if(del)
    std::filesystem::remove_all(path);
  if(!std::filesystem::exists(path))
  {
    if(!std::filesystem::create_directories(path))
    {
      if(ff_logger)
        FF_LOG_ERR("create firectory");
      return false;
    }
  }
  return true;
}

bool ff::create_config_dir(const std::string &name_of_project)
{
  std::string config_path = ff::get_config_path(name_of_project);
  return ff::create_dir(config_path);
}