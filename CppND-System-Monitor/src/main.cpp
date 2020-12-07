#include "ncurses_display.h"
#include "system.h"
#include <iostream>
int main() {
  System system;
  int process_to_display = 30;
  NCursesDisplay::Display(system, process_to_display);
}