//print.cpp
#include "../include/ff.h"

bool ff::print_lines_stream(ff::stream &stream, bool begin, int start_line, int end_line)
{
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
        return false;
      }
      if(!ffu::check_range(stream, start_line, end_line))
      {
        FF_LOG_ERR("out of range");
        return false;
      }
      std::string line;
      int line_num = 1;
      while(std::getline(stream.in_file, line))
      {
        if(line_num >= start_line && (line_num <= end_line || end_line == FF_LINE_NPOS))
          std::cout << line << "\n";
        line_num++;
      }
      return true;
    }
    break;

    case WRITE:
    {
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return false;
      }

      for(int i = start_line - 1; i <= end_line - 1; ++i)
        std::cout << stream.lines[i] << "\n";
      return true;
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
}

bool ff::print_lines(const std::string &path, int start_line, int end_line)
{
  ff::stream stream(path, READ);
  return
    ff::print_lines_stream(stream, true, start_line, end_line);
}