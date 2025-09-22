//find.cpp
#include "../include/ff.h"

ff::block ff::find_block_stream
 (ff::stream &stream, const std::string &name,
  bool begin, int start_line, int end_line)
{
  block block = {FF_LINE_NPOS, FF_LINE_NPOS};
  std::string open_tag = FF_BLOCK_OPEN_PREF + name + FF_BLOCK_OPEN_POSTF;
  std::string close_tag = FF_BLOCK_CLOSE_PREF + name + FF_BLOCK_CLOSE_POSTF;
  bool in_block = false;

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
        return block;
      }
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return block;
      }
      std::string line;
      int line_num = 1;
      while(std::getline(stream.in_file, line))
      {
        if(line_num >= start_line && (end_line == FF_LINE_NPOS || line_num <= end_line))
        {
          ffu::trim(line);
          if(!in_block && line.compare(0, open_tag.size(), open_tag) == 0)
          {
            block.start_line = line_num;
            in_block = true;
          }
          else if(in_block && line.compare(0, close_tag.size(), close_tag) == 0)
          {
            block.end_line = line_num;
            break;
          }
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
        return block;
      }
      for(int i = start_line - 1; i <= end_line - 1; ++i)
      {
        std::string tmp_str = stream.lines[i];
        ffu::trim(tmp_str);
        if(!in_block && tmp_str.compare(0, open_tag.size(), open_tag) == 0)
        {
          block.start_line = i + 1;
          in_block = true;
        }
        else if(in_block && tmp_str.compare(0, close_tag.size(), close_tag) == 0)
        {
          block.end_line = i + 1;
          break;
        }
      }
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  if(!block.found() && ff_logger)
    FF_LOG_ERR("block not found");
  return block;
}

ff::block ff::find_block
 (const std::string &path, const std::string &name,
  int start_line, int end_line)
{
  ff::stream stream(path, READ);
  ff::block b = ff::find_block_stream(stream, name, true, start_line, end_line);
  stream.close();
  return b;
}

int ff::find_line_stream
 (ff::stream &stream, const std::string &str,
  bool begin, int start_line, int end_line)
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
        return FF_LINE_NPOS;
      }
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_LINE_NPOS;
      }
      std::string line;
      int line_num = 1;
      while(std::getline(stream.in_file, line))
      {
        if(line_num >= start_line && (end_line == FF_LINE_NPOS || line_num <= end_line))
        {
          ffu::trim(line);
          if(line.compare(0, str.size(), str) == 0)
            return line_num;
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
        return FF_LINE_NPOS;
      }
      for(int i = start_line - 1; i <= end_line - 1; i++)
      {
        std::string tmp_str = stream.lines[i];
        ffu::trim(tmp_str);
        if(tmp_str.compare(0, str.size(), str) == 0)
          return i + 1;
      }
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  if(ff_logger)
    FF_LOG_ERR("line not found");
  return FF_LINE_NPOS;
}

int ff::find_line
 (const std::string &path, const std::string &str,
  int start_line, int end_line)
{
  ff::stream stream(path, READ);
  return
    ff::find_line_stream(stream, str, true, start_line, end_line);
}

int ff::find_line_for_key_stream
 (ff::stream &stream, const std::string &key,
  bool begin, int start_line, int end_line)
{
  std::string prefix = FF_KEY_PREF + key + FF_KEY_POSTF;
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
        return FF_LINE_NPOS;
      }
      if(!ffu::check_range(stream, start_line, end_line))
      {
        if(ff_logger)
          FF_LOG_ERR("out of range");
        return FF_LINE_NPOS;
      }
      std::string line;
      int line_num = 1;
      while(std::getline(stream.in_file, line))
      {
        if(line_num >= start_line && (end_line == -1 || line_num <= end_line))
        {
          ffu::ltrim(line);
          if(line.compare(0, prefix.size(), prefix) == 0)
            return line_num;
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
        return FF_LINE_NPOS;
      }
      for(int i = start_line - 1; i <= end_line - 1; i++)
      {
        std::string tmp_str = stream.lines[i];
        ffu::ltrim(tmp_str);
        if(tmp_str.compare(0, prefix.size(), prefix) == 0)
          return i + 1;
      }
    }
    break;

    default:
      FF_LOG_ERR("unknow mode");
    break;
  }
  if(ff_logger)
    FF_LOG_ERR("line not found");
  return FF_LINE_NPOS;
}

int ff::find_line_for_key
 (const std::string &path, const std::string &key,
  int start_line, int end_line)
{
  ff::stream stream(path, READ);
  return
    ff::find_line_for_key_stream(stream, key, true, start_line, end_line);
}