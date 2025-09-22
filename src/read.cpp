//read.cpp
#include "../include/ff.h"

std::string ff::read_value_stream
 (ff::stream &stream, const std::string &key,
  bool begin, int start_line, int end_line)
{
  std::string prefix = FF_KEY_PREF + key + FF_KEY_POSTF;
  switch(stream.mode)
  {
    case READ:
    {
      if(begin && stream.in_file.is_open())
      {
        stream.in_file.clear();
        stream.in_file.seekg(0);
      }
      if(!stream.in_file)
      {
        if(ff_logger)
          FF_LOG_ERR("open file for read");
        return FF_NULL_STR;
      }
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_NULL_STR;
      }
      int line_num = 1;
      std::string line;
      while(std::getline(stream.in_file, line))
      {
        if(line_num >= start_line && (end_line == FF_LINE_NPOS || line_num <= end_line))
        {
          ffu::ltrim(line);
          if(line.compare(0, prefix.size(), prefix) == 0)
            return line.substr(prefix.length());
        }
        if(end_line != FF_LINE_NPOS && line_num > end_line) break;
        line_num++;
      }
    }
    break;

    case WRITE:
    {
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_NULL_STR;
      }
      for(int i = start_line - 1; i < end_line - 1; i++)
      {
        std::string tmp_str = stream.lines[i];
        ffu::ltrim(tmp_str);
        if(tmp_str.compare(0, prefix.size(), prefix) == 0)
          return stream.lines[i].substr(prefix.length());
      }
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  if(ff_logger)
    FF_LOG_ERR("line not found");
  return FF_NULL_STR;
}

std::string ff::read_value
 (const std::string &path, const std::string &key,
  int start_line, int end_line)
{
  ff::stream stream(path, READ);
  return
    ff::read_value_stream(stream, key, true, start_line, end_line);
}

std::string ff::read_line_stream(ff::stream &stream, int line_num, bool begin)
{
  switch (stream.mode)
  {
    case READ:
    {
      if(begin && stream.in_file.is_open())
      {
        stream.in_file.clear();
        stream.in_file.seekg(0);
      }
      if(!stream.in_file)
      {
        if(ff_logger)
          FF_LOG_ERR("open file for read");
        return FF_NULL_STR;
      }
      if(line_num < 1)
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_NULL_STR;
      }
      std::string line;
      int num = 1;
      while(std::getline(stream.in_file, line))
      {
        if(num == line_num) return line;
        num++;
      }
    }
    break;

    case WRITE:
    {
      if(line_num < 1 || line_num > stream.lines.size())
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_NULL_STR;
      }
      return
        stream.lines[line_num - 1];
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  return FF_NULL_STR;
}

std::string ff::read_line(const std::string &path, int line_num)
{
  ff::stream stream(path, READ);
  return
    ff::read_line_stream(stream, line_num, true);
}