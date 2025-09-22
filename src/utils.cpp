//utils.cpp
#include "../include/ff.h"

void ffu::trim(std::string &str)
{
  size_t start_pos = 0;
  while(start_pos < str.size() && std::isspace((unsigned char)str[start_pos]))
    start_pos++;
  str.erase(0, start_pos);

  size_t end_pos = str.size();
  while(end_pos > 0 && std::isspace((unsigned char)str[end_pos - 1]))
    end_pos--;
  str.erase(end_pos);
}

void ffu::ltrim(std::string &str)
{
  size_t start_pos = 0;
  while(start_pos < str.size() && std::isspace((unsigned char)str[start_pos]))
    start_pos++;
  str.erase(0, start_pos);
}

void ffu::rtrim(std::string &str)
{
  size_t end_pos = str.size();
  while(end_pos > 0 && std::isspace((unsigned char)str[end_pos - 1]))
    end_pos--;
  str.erase(end_pos);
}

bool ffu::check_range(ff::stream &stream, int start_line, int &end_line)
{
  switch(stream.mode)
  {
    case READ:
    {
      if(start_line < 1)
        return false;
      if(end_line != FF_LINE_NPOS && start_line > end_line)
        return false;
    }
    break;

    case WRITE:
    {
      if(start_line < 1)
        return false;
      if(end_line == FF_LINE_NPOS)
        end_line = stream.lines.size() + 1;
      if(start_line > end_line)
        return false;
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  return true;
}