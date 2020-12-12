#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  string version;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization // Come back here
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float value;
  float memutilization{0.0};
  std::vector<float> memvalues{};
  std::ifstream filestream(kProcDirectory+ kMeminfoFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream(line);
    for (size_t i = 0; i < 5; i++)
    {
      /*read the first five values from meminfo, push it into a vector and then apply the formula */
      line  >> key >> value;
      memvalues.push_back(value);
    }

    memutilization = (memvalues.at(0) - memvalues.at(1) - memvalues.at(2) - memvalues.at(3)- memvalues.at(4)) / memvalues.at(0);
    return (memutilization*100);
  }
  return memutilization;
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long uptime{0};  
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
    return uptime;
  }

  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  long value;
  long jiffies{0};
  string cpustring;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpustring;
    while (linestream >> value)
    {
      /* code */
      jiffies += value;
    }
    
  }
  return jiffies; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line;
  string key;
  long value{0};
  long activejiffies{0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for (size_t i = 0; i < 13; i++)
    {
      /* code */
      linestream >> key;
    }  

    for (size_t i = 0; i < 4; i++)
    {
      /* code */
      linestream >> value;
      activejiffies += value;
    }
    return activejiffies;    

  }

   return activejiffies;
  }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string cpu;
  long value;
  vector<long> cpujiffies;
  long activejiffies{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    while (linestream >> value)
    {
      /* code */
      cpujiffies.push_back(value);
    }       
  }

  activejiffies = cpujiffies.at(CPUStates::kUser_) + cpujiffies.at(CPUStates::kNice_) + cpujiffies.at(CPUStates::kSystem_)
                  + cpujiffies.at(CPUStates:: kIRQ_) + cpujiffies.at(CPUStates:: kSoftIRQ_) + cpujiffies.at(CPUStates::kSteal_ );

  return activejiffies; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {

  string line;
  string cpu;
  long value;
  vector<long> cpujiffies;
  long idlejiffies{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    while (linestream >> value)
    {
      /* code */
      cpujiffies.push_back(value);
    }       
  }

  idlejiffies = cpujiffies.at(CPUStates::kIdle_) + cpujiffies.at(CPUStates::kIOwait_) ;                

  return idlejiffies;
   
   }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 

  string line;
  string key;
  int value{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
       std::istringstream linestream(line);
       linestream >> key >> value;
       if(key == "processes")
       return value;       
    } 
  }
  return value; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

  
  string line;
  string key;
  int value{0};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
       std::istringstream linestream(line);
       linestream >> key >> value;
       if(key == "procs_running")
       return value;       
    }  
  }
  return value; 
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
    if(filestream.is_open())
    {
      std::getline( filestream, line);
      return line;

    }
   return line;
   }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::Ram(int pid) { 

  string line, key ;
  float value{0.0};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open())
  {
    while(std::getline( filestream, line))
    {
      std::istringstream linestream(line);
      while ( linestream >> key >> value )
      {
        /* code */
        if ( key == "VmSize:")
        {
          /* code */
          return value/ 1024.00;
        }     

      }
      
    }  
   
  }
   return value; 
  }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {

  string line;
  string key;
  string value{};
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if(filestream.is_open())
  {
    while(std::getline( filestream, line))
    {
      std::istringstream linestream(line);
      while (linestream >> key  >> value)
      {
        /* code */
        if(key == "Uid:")
        {
          return value;
        }
      }
    }      
  }
   return value;   
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  // string line, key, value{};
  // string  uid = Uid(pid);
  // std::ifstream filestream(kPasswordPath);
  // if(filestream.is_open()) 
  // {
  //   while (std::getline(filestream , line))
  //   {
  //     /* code */
  //     std::replace(line.begin(), line.end(), ":", " ");
  //     std::replace(line.begin(), line.end(), "x", " ");
  //     std::istringstream linestream(line);
  //     while(linestream >>  value >> key)
  //     {
  //         if(key == uid)
  //         {
  //           return value;
  //         }
  //     }

  //   }
    
  // }
  return string{}; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { return 0; }