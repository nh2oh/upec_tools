#include "tablefile.h"
#include <iostream>
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


int main() {

	std::string expect_header {"	contig_id	feature_id	type	location	start	stop	strand	function	aliases	figfam	evidence_codes	nucleotide_sequence	aa_sequence		"};
	std::string delim {"\ts"};
	auto vs = strtok(expect_header,delim);


	/*
	std::string file_uti12 {"C:/Users/ben/Desktop/cpp/git/upec_tools/tables/UTI12_table.txt"};
	auto uti12 = read_tablefile(file_uti12);
	auto uti12_is_valid = check_tablefile(uti12);
	std::string file_uti21{"C:/Users/ben/Desktop/cpp/git/upec_tools/tables/UTI21_table.txt"};
	auto uti21 = read_tablefile(file_uti21);
	auto uti21_is_valid = check_tablefile(uti21);

    std::cout << uti12_is_valid << ", " << uti21_is_valid << std::endl;
	*/
	return 0;
}



