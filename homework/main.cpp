#include <ctime>
#include <iostream>
#include <string>
using namespace std;

// exceptionlar
class MyException {
public:
  string message;
  MyException(string message) { this->message = message; }

  string Message() const { return message; }
};

class FileExistsException : public MyException {
public:
  FileExistsException(string message) : MyException(message) {}
};

class FileSizeExceededException : public MyException {
public:
  FileSizeExceededException(string message) : MyException(message) {}
};

class InvalidFileException : public MyException {
public:
  InvalidFileException(string message) : MyException(message) {}
};

class NofileExeption : public MyException {
public:
  NofileExeption(string message) : MyException(message) {}
};

class FilenotFoundExeption : public MyException {
public:
  FilenotFoundExeption(string message) : MyException(message) {}
};

// disk
class Disk {
  double current_size = 0;

private:
  // file classi
  class File {
  private:
    double file_size;

  public:
    string filename;
    string content;
    double getfile_size() { return file_size; }
    File(string filename, string content = "") {
      this->filename = filename;
      this->content = content;
      file_size = content.length() / 10;
    }
  };

  File **files;
  int file_count;

public:
  const static double max_size;
  // funksiyalar
  File &getFile(string filename) {
    if (file_count == 0) {
      throw new NofileExeption("There is no file");
    }
    if (filename.length() <= 0) {
      throw new InvalidFileException("Filename can't be empty");
    }
    if (!DoesFileExist(filename)) {
      throw new FilenotFoundExeption("There is no such file");
    }
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == filename) {
        return *files[i];
      }
    }
  }

  bool DoesFileExist(string filename) {
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == filename) {
        return true;
      }
    }
    return false;
  }

  void createFile(string filename, string content = "") {
    if (max_size <= current_size + content.length()) {
      throw new FileSizeExceededException("Disk is full or file is too big");
    }
    if (filename.length() <= 0) {
      throw new InvalidFileException("Filename can't be empty");
    }
    if (DoesFileExist(filename)) {
      throw new FileExistsException("Such file already exists");
    }
    File *new_file = new File(filename, content);
    files[file_count] = new_file;
    file_count++;
    current_size += content.length();
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    std::cout << "time created" << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
  }

  void setFileContent(string filename, string content = "") {
    File &file = getFile(filename);
    file.content = content;
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    std::cout << "time changed" << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
  }

  void DeleteFileContent(string filename) {
    if (file_count == 0) {
      throw new NofileExeption("There is no file");
    }
    if (filename.length() <= 0) {
      throw new InvalidFileException("Filename can't be empty");
    }
    if (!DoesFileExist(filename)) {
      throw new FilenotFoundExeption("There is no such file");
    }
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == filename) {
        delete files[i];
        files[i] = NULL;
        file_count--;
        current_size -= files[i]->getfile_size();
        return;
      }
    }
  }

  string updateFilename(string oldfilename, string newfilename) {
    if (file_count == 0) {
      throw new NofileExeption("There is no file");
    }
    if (oldfilename.length() <= 0) {
      throw new InvalidFileException("Filename can't be empty");
    }
    if (!DoesFileExist(oldfilename)) {
      throw new FilenotFoundExeption("There is no such file");
    }
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == oldfilename) {
        files[i]->filename = newfilename;
        return newfilename;
      }
    }
  }

  string hashFile(string filename) {
    const std::hash<std::string> hasher;
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == filename) {
        const auto hashcontent = hasher(files[i]->content);
        return std::to_string(hashcontent);
      }
    }
  }

  void deleteFileByFilename(string filename) {
    if (file_count == 0) {
      throw new NofileExeption("There is no file");
      return;
    }
    if (filename.length() <= 0) {
      throw new InvalidFileException("Filename can't be empty");
      return;
    }
    if (!DoesFileExist(filename)) {
      throw new FilenotFoundExeption("There is no such file");
      return;
    }
    for (int i = 0; i < file_count; i++) {
      if (files[i]->filename == filename) {
        delete files[i];
        files[i] = NULL;
        file_count--;
        current_size -= files[i]->getfile_size();
        return;
      }
    }
    throw new FilenotFoundExeption("There is no such file");
  }

  void showAllFiles() {
    for (int i = 0; i < file_count; i++) {
      cout << files[i]->filename << " " << files[i]->content << endl;
    }
  }
};
// HDD
class HDD {
private:
  string filename;
  string content;
  int downspeed = 10;

public:
  HDD(string filename, string content) {
    createFile(filename, content);
    double downtime = content.length() / downspeed;
  }
};
class SSD {
private:
  string filename;
  string content;
  int downspeed = 100;

public:
  SSD(string filename, string content) {
    createFile(filename, content);
    double downtime = content.length() / downspeed;
  }
};
// disk size
const double Disk::max_size = 1024;
// operationsystem
class OperationSystem {
  OperationSystem() {}

public:
  static void controlPC();
};
// controlpc
void OperationSystem::controlPC() {
  Disk hd;
  try {
    hd.createFile("newtext.txt", "hello world");
  } catch (const char *ex) {
    cout << "Error : " << ex << endl;
  }
}
// main
int main() { OperationSystem::controlPC(); }