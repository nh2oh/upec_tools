#pragma once
#include <string>
#include <filesystem>
#include <vector>

struct tablefile_entry {
	std::string contig_id {};
	std::string feature_id {};
	std::string type {};
	std::string location {};
	int64_t start {};
	int64_t stop {};
	bool strand {};
	std::string function {};
	std::string aliases {};
	std::string figfam {};
	std::string evidence_codes {};
	std::string nucleotide_sequence {};
	std::string aa_sequence {};
};


struct tablefile {
	std::filesystem::path file {};
	std::vector<tablefile_entry> data {};
};

tablefile read_tablefile(const std::filesystem::path&);

bool check_tablefile(const tablefile&);

std::string tablefile2fastafile(const tablefile&, const std::filesystem::path&);


