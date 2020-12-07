#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
 public:
  Process(const int pid, const long total_jiffies);
  int Pid();                         
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  
  void calculateCpuUtilization(const long total_jiffies);

 private:
  int pid_;
  float cpu_utilization_;
};

#endif