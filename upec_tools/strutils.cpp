#include "strutils.h"
#include <string>
#include <vector>
#include <algorithm>

// Split a string at instances of tk, stripping the tk's from the result.  
std::vector<std::string> strtok(const std::string& s, const std::string& tk) {
	std::vector<std::string> vs {};
	
	auto p_s {s.begin()}; auto p_e {s.begin()};
	while (true) {
		p_s = p_e;
		p_e = std::search(p_s,s.end(),tk.begin(),tk.end());
		vs.push_back({p_s, p_e});

		if (p_e == s.end()) { break; }
		p_e += tk.size();
	}

	return vs;
}
