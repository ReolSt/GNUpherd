#include "file_manager.hpp"
bool FileManager::
read_file(const std::string& fname)  {
  std::ifstream file(fname,std::ios::in);
  if(file.fail()) {
    return false;
  }
  _stream << file.rdbuf();
  file.close();
  _file_name=fname;
  return true;
}

bool FileManager::
write_file(const std::string& fname,
                const std::deque<std::string>& buf) {
  std::ofstream file(fname);
  if(file.fail()) {
    return false;
  }
  for(auto i : buf) {
    file << i << "\n";
  }
  return true;
}

const std::string& FileManager::
list_directory() {
  std::string command = "cd " + _path + "&& ls -l";
  FILE *fp = popen(command.c_str(),"r");
  char buf[999];
  if(fp == NULL) {
    exit(1);
  }
  _command_output.clear();
  while(fgets(buf,900,fp)) {
    _command_output.append(buf);
  }
  return _command_output;
}

bool FileManager::
change_directory(const std::string& dname) {
  if(dname[0] == '/') {
    _path=dname;
  }
  else if(dname == "..") {
    _path.pop_back();
    _path = _path.substr(0,_path.rfind('/')+1);
  }
  else if(dname != "."){
    _path+= "/" + dname + (dname.back()=='/'?"":"/");
  }
  return true;
}
