// ff.h
// ff is a simple files and configs library with a mini read-parser and writer
// uses a simple [key] = value structure and some functions:

// get:
//   path
//   count

// find:
//   line
//   block
//   line for key

// create:
//   file
//   dir

// read:
//   value
//   line

// write:
//   value
//   line
//   block tag

// check exists:
//   file
//   dir

// remove:
//   file
//   dir
//   line
//   lines
//   block

// copy:
//   files

// print:
//   lines

// also has some utils functions:

// trim:
//   left
//   right
//   double

// check range:
//   for READ mode
//   for WRITE mode

// use 1-based indexing in set line nums !!!

#ifndef FF_LIB
#define FF_LIB

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

// base tags
#define FF_ERR "ERROR -> "
#define FF_WARN "WARNING -> "
#define FF_NULL_STR ""
#define FF_LINE_NPOS -1
#define FF_TEMP_POSTF "_temp"

// blocks tags
#define FF_BLOCK_OPEN_PREF "<"
#define FF_BLOCK_OPEN_POSTF ">"
#define FF_BLOCK_CLOSE_PREF "</"
#define FF_BLOCK_CLOSE_POSTF ">"

// key-value tags
#define FF_KEY_PREF "["
#define FF_KEY_POSTF "] = "

// loggers
#define FF_LOG_ERR(msg) std::cout << FF_ERR << msg << " ->> " << __func__ << "\n";
#define FF_LOG_WARN(msg) std::cout << FF_WARN<< msg << " ->> " << __func__ << "\n";
#define FF_LOG_ERR_NO_FUNC(msg) std::cout << FF_ERR << msg << "\n";
#define FF_LOG_WARN_NO_FUNC(msg) std::cout << FF_WARN << msg << "\n";

enum FF_STREAM_MODE
{
  READ,
  WRITE
};

enum FF_BLOCK_TAG
{
  OPEN,
  CLOSE
};

// main lib namespace
namespace ff
{
  struct block
  {
    int start_line;
    int end_line;
    bool found()
    {
      return true ? (start_line != FF_LINE_NPOS && end_line != FF_LINE_NPOS) : false;
    }
  };

  // main ff stream
  struct stream
  {
    std::vector<std::string> lines;
    std::ifstream in_file;
    std::string path;
    FF_STREAM_MODE mode;
    // closed var need for once close
    bool closed = false;
    stream(const std::string &path, FF_STREAM_MODE mode)
    {
      this->path = path;
      this->mode = mode;
      // anyway open read stream
      in_file.open(path);
      if(in_file)
      {
        // fill vector only in WRITE mode
        if(mode == WRITE)
        {
          lines.clear();
          std::string line;
          while(std::getline(in_file, line))
          {
            lines.push_back(line);
          }
        }
      }
      else
      {
        FF_LOG_ERR("open file for read")
      }
    }
    // set reader to start
    void clear_stream()
    {
      in_file.clear();
      in_file.seekg(0);
    }
    // short get string count
    int str_count()
    {
      return lines.size();
    }
    // write lines to file
    void write_buffer()
    {
      if(mode == WRITE)
      {
        std::ofstream out_file_temp;
        out_file_temp.open(path + FF_TEMP_POSTF);
        for(auto &line : lines)
        {
          out_file_temp << line << "\n";
        }
        out_file_temp.close();
      }
      else
        FF_LOG_ERR("called in READ mode!");
    }
    // close all stream
    void close()
    {
      if(closed) return;
      in_file.close();
      if(mode == WRITE)
      {
        write_buffer();
        std::remove(path.c_str());
        std::filesystem::rename(path + FF_TEMP_POSTF, path);
        lines.clear();
      }
      closed = true;
    }
    ~stream()
    {
      close();
    }
  };

  // get
  std::string get_home_path();
  // config path is "/home/username/.config/name_of_project" on linux
  // and "C:\users\username\AppData\local\name_of_project" on windows
  std::string get_config_path(const std::string &name_of_project);
  int get_str_count_stream(ff::stream &stream);
  int get_str_count(const std::string &path);

  // find
  ff::block find_block_stream
   (ff::stream &stream, const std::string &name,
    bool begin = true, int start_line = 1, int end_line = FF_LINE_NPOS);
  ff::block find_block
   (const std::string &path, const std::string &name,
    int start_line = 1, int end_line = FF_LINE_NPOS);
  int find_line_stream
   (ff::stream &stream, const std::string &str,
    bool begin = true, int start_line = 1, int end_line = FF_LINE_NPOS);
  int find_line
   (const std::string &path, const std::string &str,
    int start_line = 1, int end_line = FF_LINE_NPOS);
  int find_line_for_key_stream
   (ff::stream &stream, const std::string &key,
    bool begin = true, int start_line = 1, int end_line = FF_LINE_NPOS);
  int find_line_for_key
   (const std::string &path, const std::string &key,
    int start_line = 1, int end_line = FF_LINE_NPOS);
  

  // create
  bool create_file(const std::string &path, bool del = false);
  bool create_dir(const std::string &path, bool del = false);
  bool create_config_dir(const std::string &name_of_project);

  // read
  std::string read_value_stream
   (ff::stream &stream, const std::string &key,
    bool begin = true, int start_line = 1, int end_line = FF_LINE_NPOS);
  std::string read_value
   (const std::string &path, const std::string &key,
    int start_line = 1, int end_line = FF_LINE_NPOS);
  std::string read_line_stream(ff::stream &stream, int line_num, bool begin = true);
  std::string read_line(const std::string &path, int line_num);

  // write
  bool write_value_stream
   (ff::stream &stream, const std::string &key, const std::string &value,
    int tab_l = 0, int start_line = 1, int end_line = FF_LINE_NPOS);
  bool write_value
   (const std::string &path, const std::string &key, const std::string &value,
    int tab_l = 0, int start_line = 1, int end_line = FF_LINE_NPOS);
  // добавить таб л и перенести лайцн нам в конец для (оставить пустой для добавления в конец файла)
  bool write_line_stream(ff::stream &stream, const std::string &str, int tab_l = 0, int line_num = FF_LINE_NPOS);
  bool write_line(const std::string &path, const std::string &str, int tab_l = 0, int line_num = FF_LINE_NPOS);
  bool write_block_tag_stream(ff::stream &stream, const std::string &name, FF_BLOCK_TAG tag_type, int tab_l = 0, int line_num = FF_LINE_NPOS);
  bool write_block_tag(const std::string &path, const std::string &name, FF_BLOCK_TAG tag_type, int tab_l = 0, int line_num = FF_LINE_NPOS);

  // check
  bool file_exists(const std::string &path);
  bool dir_exists(const std::string &path);

  // remove
  bool remove(const std::string &path);

  bool remove_line_stream(ff::stream &stream, int line_num, bool change_to_empty_str = false);
  bool remove_line(const std::string &path, int line_num, bool change_to_empty_str = false);
  bool remove_lines_stream(ff::stream &stream, int start_line, int end_line, bool change_to_empty_str = false);
  bool remove_lines(const std::string &path, int start_line, int end_line, bool change_to_empty_str = false);
  bool remove_block_stream(ff::stream &stream, const std::string &name);
  bool remove_block(const std::string &path, const std::string &name);

  // copy
  bool copy(const std::string &from_path, const std::string &to_path);

  // print
  bool print_lines_stream(ff::stream &stream,bool begin = true, int start_line = 1, int end_line = FF_LINE_NPOS);
  bool print_lines(const std::string &path, int start_line = 1, int end_line = FF_LINE_NPOS);
}

// utils lib namespace
namespace ffu
{
  // trims
  void trim(std::string &str);
  void ltrim(std::string &str);
  void rtrim(std::string &str);

  bool check_range(ff::stream &stream, int start_line, int &end_line);
}

// view log lever
inline bool ff_logger = true;

#endif // FF_LIB