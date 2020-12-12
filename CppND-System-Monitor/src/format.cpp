#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {

    long hourconverter = 3600;
    long minsconvertor = 60;

    long hours = seconds / hourconverter;
    int mins = (seconds % hourconverter) / minsconvertor;
    int secs = seconds % minsconvertor;

    return std::to_string(hours) + ":" + std::to_string(mins) + ":"+std::to_string(secs);
 }
