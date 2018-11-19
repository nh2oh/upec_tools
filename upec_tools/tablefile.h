#pragma once
#include <string>
#include <filesystem>
#include <vector>

//
// A tab-delimeted txt file as created by Rasko for the UTI12, UTI21 genomes
//
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

//
// Basic statistics... number of RNA, protein CDS's, etc
//
struct tablefile_stats {
	int64_t num_rna {0};
	int64_t num_prot {0};
	int64_t mean_len_prot {0};
	int64_t mean_len_rna {0};
};
tablefile_stats calc_tablefilestats(const tablefile&);


struct dbk_interest {
	std::string name {};
	int64_t start {};
	int64_t stop {};
	std::string function {};
};

std::vector<dbk_interest> annotate_dbk_interest(const std::filesystem::path&, const tablefile&);
