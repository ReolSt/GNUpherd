#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

class FileManager {
public:
  inline FileManager():_path("/home/emacs/"){}
  bool read_file(const std::string& fname);
  bool write_file(const std::string& fname,
                  const std::deque<std::string>& buf);
  const std::string& list_directory();
  bool change_directory(const std::string& dname);
  inline void clear() {_stream.clear();}
  inline const std::string full_file_name() {
    return _path + "_file_name";
  }
  inline std::stringstream& stream() {return _stream;}
  inline const std::string& command_output() {return _command_output;}
protected:
  std::string _path;
  std::string _file_name;
  std::stringstream _stream;
  std::string _command_output;
private:
};
#endif
