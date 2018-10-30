#pragma once
#include <string>
#include <filesystem>

struct fasta_genome {
	std::filesystem::path file {};
	std::string header {};
	std::string seq {};
};

fasta_genome read_fgfile(const std::filesystem::path&);


struct fasta_entry {
	std::string header {};
	/*std::string gene {};
	std::string locus_tag {};
	std::string protein {};
	std::string protein_id {};
	std::string location {};
	std::string gbkey {};*/
	std::string seq {};
};

struct fastafile {
	std::filesystem::path file {};
	std::vector<fasta_entry> data {};
};

fastafile read_fastafile(const std::filesystem::path&);
