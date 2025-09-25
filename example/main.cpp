// main.cpp
// example preview file (mini programm)
#include "../include/ff.h"

#define NAME "ff_example_app"

int main()
{
  // you can get just home or full config path
  std::string home_path = ff::get_home_path();
  std::string config_path = ff::get_config_path(NAME);
  std::cout << "1.home path: " << home_path << "\n2.config path: " << config_path << "\n";

  // you also can create config dir without getting config path
  ff::create_config_dir(NAME);

  std::string filename = config_path + "test.txt";

  // but you must have full path for create file
  ff::create_file(filename);
  // if you want delete old file, set true flag
  ff::create_file(config_path + "test_2.txt", true);

  // func return 1-based strings count in file
  int strings_count = ff::get_str_count(config_path + "test.txt");
  std::cout << "3.strings count: " << strings_count << "\n";

  // logger print errors and warnings
  // you can stop logging
  ff_logger = false;
  // and start again
  ff_logger = true;

  // can write any line > 1 string
  ff::write_line(filename, "first string", 0, 1);
  ff::write_line(config_path + "test_2.txt", "first string", 0, 10);

  std::string key = "first key";
  // can write [key] = value string
  // tab_l set spaces before key-value structure
  // start line set first line in found range
  // end line set last line in found range:
  //   if you not set end line, find will be to end file
  //   if you set end line > end file, file will be resizing to end line
  ff::write_value(filename, key, "any value", 10, 1, 10);

  // can read string
  std::string first_value = ff::read_value(filename, key);
  std::cout << "4.value: " << first_value << "\n";

  // can write block tags OPEN and CLOSE
  ff::write_block_tag(filename, "block", OPEN);
  ff::write_block_tag(filename, "block", CLOSE);

  // check file lines
  ff::print_lines(filename);

  // can find block
  ff::block b;
  b = ff::find_block(filename, "block");

  // check block found state
  if(b.found())
    std::cout << "5.start block: " << b.start_line << "\n6.end block: " << b.end_line << "\n";
  else
    std::cout << "5.6.block not found\n";

  // remove block
  std::cout << "\n7.file after remove block:\n";
  ff::remove_block(filename, "block");
  ff::print_lines(filename);

  // write block if it does not exist
  ff::block b2 = ff::find_block(filename, "b2", 4, 6);
  if(!b2.found())
  {
    ff::write_block_tag(filename, "b2", OPEN, 0, 4);
    ff::write_block_tag(filename, "b2", CLOSE, 0, 6);
  }

  // use stream if need call a lot of functions
  ff::stream stream(filename, WRITE);
  ff::write_value_stream(stream, "stream key", "stream value");
  stream.close();

  ff::stream read_stream(filename, READ);
  std::cout << "8.value: " << ff::read_value_stream(read_stream, "stream key") << "\n";
  read_stream.close();

  // you also can use ffu functions
  std::string name = "   name    ";
  std::cout << "9.src: {" << name << "}\n";
  ffu::ltrim(name);
  std::cout << "10.after ltrim: {" << name << "}\n";
  ffu::rtrim(name);
  std::cout << "11.after ltrim and rtrim: {" << name << "}\n";

  if(ff::find_line(filename, "once str") == FF_LINE_NPOS)
    ff::write_line(filename, "once str");

  // anyway write
  ff::write_line(filename, "EOF");

  return 0;
}
