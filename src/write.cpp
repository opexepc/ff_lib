//write.cpp
#include "../include/ff.h"

bool ff::write_value_stream
 (ff::stream &stream, const std::string &key, const std::string &value,
  int tab_l, int start_line, int end_line)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  int cycle_end = end_line;
  if(stream.lines.size() == 0)
    stream.lines.push_back(FF_NULL_STR);
  if(end_line == FF_LINE_NPOS)
    cycle_end = stream.lines.size();
  else if(cycle_end > stream.lines.size())
    cycle_end = stream.lines.size();
  if(start_line < 1 || start_line > cycle_end)
  {
    if(ff_logger)
      FF_LOG_ERR("out of range");
    return false;
  }
  bool found = false;
  std::string tab(tab_l, ' ');
  std::string prefix = FF_KEY_PREF + key + FF_KEY_POSTF;

  for(int i = start_line - 1; i < cycle_end; ++i)
  {
    std::string tmp_str = stream.lines[i];
    ffu::ltrim(tmp_str);
    if(tmp_str.compare(0, prefix.size(), prefix) == 0)
    {
      found = true;
      stream.lines[i] = tab + prefix + value;
      break;
    }
  }
  if(!found)
  {
    if(end_line == FF_LINE_NPOS)
      stream.lines.push_back(tab + prefix + value);
    else if(end_line <= stream.lines.size())
      stream.lines.insert(stream.lines.begin() + (end_line - 1), tab + prefix + value);
    else
    {
      stream.lines.resize(end_line - 1, FF_NULL_STR);
      stream.lines.push_back(tab+ prefix + value);
    }
  }
  return true;
}

bool ff::write_value
 (const std::string &path, const std::string &key, const std::string &value,
  int tab_l, int start_line, int end_line)
{
  ff::stream stream(path, WRITE);
  return
    ff::write_value_stream(stream, key, value, tab_l, start_line, end_line);
}

bool ff::write_line_stream(ff::stream &stream, const std::string &str, int tab_l, int line_num)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  if(line_num < 1 && line_num != FF_LINE_NPOS)
  {
    if(ff_logger)
      FF_LOG_ERR("out of range");
    return false;
  }
  std::string tab(tab_l, ' ');
  if(line_num == FF_LINE_NPOS)
    stream.lines.push_back(tab+ str);
  else if(line_num <= stream.lines.size())
    stream.lines[line_num - 1] = tab+ str;
  else
  {
    stream.lines.resize(line_num - 1, FF_NULL_STR);
    stream.lines.push_back(tab+ str);
  }
  return true;
}

bool ff::write_line(const std::string &path, const std::string &str, int tab_l, int line_num)
{
  ff::stream stream(path, WRITE);
  return
    ff::write_line_stream(stream, str, tab_l, line_num);
}

bool ff::write_block_tag_stream(ff::stream &stream, const std::string &name, FF_BLOCK_TAG tag_type, int tab_l, int line_num)
{
  if(stream.mode != WRITE)
  {
    if(ff_logger)
      FF_LOG_ERR("stream mode not is WRITE");
    return false;
  }
  std::string correct_pref, correct_postf;
  switch(tag_type)
  {
    case OPEN:
      correct_pref = FF_BLOCK_OPEN_PREF;
      correct_postf = FF_BLOCK_OPEN_POSTF;
    break;

    case CLOSE:
      correct_pref = FF_BLOCK_CLOSE_PREF;
      correct_postf = FF_BLOCK_CLOSE_POSTF;
    break;

    default:
      FF_LOG_ERR("unknow tag type");
      return false;
    break;
  }
  return ff::write_line_stream(stream, correct_pref + name + correct_postf, tab_l, line_num);
}

bool ff::write_block_tag(const std::string &path, const std::string &name, FF_BLOCK_TAG tag_type, int tab_l, int line_num)
{
  ff::stream stream(path, WRITE);
  return
    ff::write_block_tag_stream(stream, name, tag_type, tab_l, line_num);
}
