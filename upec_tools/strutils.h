#pragma once
#include <string>
#include <vector>


// Split a string at instances of tk, stripping the tk's from the result.  
std::vector<std::string> strtok(const std::string&, const std::string&);

// Extract delimited fields within a string.  
//std::vector<std::string> strfields(const std::string&, const std::string&, const std::string&);
