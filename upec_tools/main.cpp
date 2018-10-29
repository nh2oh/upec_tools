#include "tablefile.h"
#include <iostream>

int main() {
	std::string file_uti12 {"C:/Users/ben/Desktop/cpp/git/upec_tools/tables/UTI12_table.txt"};
	auto uti12 = read_tablefile(file_uti12);
	auto uti12_is_valid = check_tablefile(uti12);
	std::string file_uti21{"C:/Users/ben/Desktop/cpp/git/upec_tools/tables/UTI21_table.txt"};
	auto uti21 = read_tablefile(file_uti21);
	auto uti21_is_valid = check_tablefile(uti21);

    std::cout << uti12_is_valid << ", " << uti21_is_valid << std::endl;
	return 0;
}



