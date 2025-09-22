//remove.cpp
#include "../include/ff.h"

bool ff::remove(const std::string &path)
{
  return
    std::filesystem::remove_all(path) > 0;
}

bool ff::remove_line_stream(ff::stream &stream, int line_num, bool change_to_empty_str)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  if(line_num < 1 || line_num > stream.lines.size())
  {
    if(ff_logger)
      FF_LOG_ERR("out of range");
    return false;
  }
  if(change_to_empty_str)
    stream.lines[line_num - 1] = FF_NULL_STR;
  else
    stream.lines.erase(stream.lines.begin() + line_num - 1);
  return true;
}

bool ff::remove_line(const std::string &path, int line_num, bool change_to_empty_str)
{
  ff::stream stream(path, WRITE);
  return
    ff::remove_line_stream(stream, line_num, change_to_empty_str);
}

bool ff::remove_lines_stream(ff::stream &stream, int start_line, int end_line, bool change_to_empty_str)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  if(start_line < 1 || end_line > stream.lines.size() || start_line > end_line)
  {
    if(ff_logger)
      FF_LOG_ERR("out of range");
    return false;
  }
  if(change_to_empty_str)
    for(int i = end_line - 1; i >= start_line - 1; --i)
    {
      stream.lines[i] = FF_NULL_STR;
    }
  else
    stream.lines.erase(stream.lines.begin() + start_line - 1, stream.lines.begin() + end_line);
  return true;
}

bool ff::remove_lines(const std::string &path, int start_line, int end_line, bool change_to_empty_str)
{
  ff::stream stream(path, WRITE);
  return
    ff::remove_lines_stream(stream, start_line, end_line, change_to_empty_str);
}

bool ff::remove_block_stream(ff::stream &stream, const std::string &name)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  block b = ff::find_block_stream(stream, name, 1, 1, FF_LINE_NPOS);
  if(!b.found())
    return false;
  ff::remove_lines_stream(stream, b.start_line, b.end_line, false);
  return true;
}

bool ff::remove_block(const std::string &path, const std::string &name)
{
  ff::stream stream(path, WRITE);
  return
    ff::remove_block_stream(stream, name);
}