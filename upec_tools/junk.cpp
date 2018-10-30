#include "tablefile.h"
#include "strutils.h"
#include <iostream>
#include <vector>
#include <string>




int junk() {

	std::string expect_header{"contig_id	feature_id	type	location	start	stop	strand	function	aliases	figfam	evidence_codes	nucleotide_sequence	aa_sequence"};
	std::string delim{"\t"};
	auto vs = strtok(expect_header, delim);

	std::string file_uti12{"..\\tables\\UTI12_table.txt"};
	auto uti12 = read_tablefile(file_uti12);
	auto uti12_is_valid = check_tablefile(uti12);
	std::string file_uti21{"..\\tables\\UTI21_table.txt"};
	auto uti21 = read_tablefile(file_uti21);
	auto uti21_is_valid = check_tablefile(uti21);

	std::cout << uti12_is_valid << ", " << uti21_is_valid << std::endl;

	return 0;
}



