#include "fasta_genome.h"
#include "strutils.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

fasta_genome read_fgfile(const std::filesystem::path& fp) {
	std::fstream fs {fp, std::ios::in};
	if (!fs.is_open() || fs.fail()) {
		std::cout << "Error opening file:  " << std::filesystem::absolute(fp) << std::endl;
		std::abort();
	}

	fasta_genome res {};  res.file = fp;  // "result"

	std::string cl{};  // "current line"
	std::getline(fs, cl);  // The first line must be the expected col headers
	if (cl.size() < 1 || cl[0] != '>') {
		std::cout << "Error reading header line: Expected > ... , Instead got:\n"
			<< cl << std::endl;
		std::abort();
	}
	res.header = cl;

	while (!fs.eof()) {
		std::getline(fs, cl);
		if (cl.size() == 0) {
			continue;
		};

		res.seq.append(cl);
	}

	return res;
}





fastafile read_fastafile(const std::filesystem::path& fp) {
	std::fstream fs {fp, std::ios::in};
	if (!fs.is_open() || fs.fail()) {
		std::cout << "Error opening file:  " << std::filesystem::absolute(fp) << std::endl;
		std::abort();
	}

	fastafile res {};  res.file = fp;  // "result"

	bool in_header {false};
	std::string cl {};  // "current line"
	fasta_entry curr_entry{};

	std::getline(fs, cl);
	while (!fs.eof()) {
		if (cl.size() == 0) { continue; };  // Skip blank lines
		if (cl[0] == '>') {
			curr_entry.header = cl;
			/*
			auto hf = strfields(cl,"[","]");
			curr_entry.gene = hf[1];
			curr_entry.locus_tag = hf[2];
			curr_entry.protein = hf[3];
			curr_entry.protein_id = hf[4];
			curr_entry.location = hf[5];
			curr_entry.gbkey = hf[6];
			*/
		} else {
			std::abort();
		}
		while (!fs.eof()) {
			std::getline(fs, cl);
			if (cl.size() == 0) { continue; };
			if (cl[0] == '>') {	
				break;
			}
			curr_entry.seq.append(cl);
		}
		res.data.push_back(curr_entry);
		curr_entry.header = ""; curr_entry.seq = "";
	}
	
	return res;
}





