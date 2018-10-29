#include "tablefile.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cmath>

// Skips the first line of the file, assumed to be the header
tablefile read_tablefile(const std::filesystem::path& fp) {
	std::fstream fs {fp,std::ios::in};
	if (!fs.is_open() || fs.fail()) {
		std::cout << "Error opening file:  " << std::filesystem::absolute(fp) << std::endl;
		std::abort();
	}

	tablefile res {};  res.file = fp;  // "result"
	
	std::string delim {'\t'};
	std::string cl {};  // "current line"
	std::string expect_header{"contig_id	feature_id	type	location	start	stop	strand	function	aliases	figfam	evidence_codes	nucleotide_sequence	aa_sequence"};

	std::getline(fs, cl);  // The first line must eb the expected col headers
	if (cl != expect_header) {
		std::cout << "Error reading header" << std::endl;
		std::abort();
	}
	while (!fs.eof()) {
		std::getline(fs,cl);
		if (cl.size() == 0) {
			continue;
		};

		tablefile_entry curr_tfe {};

		size_t spos{0}; size_t epos{0};
		epos = cl.find(delim,spos);
		curr_tfe.contig_id = cl.substr(spos,epos);
		cl.erase(0, epos+delim.size());
		
		epos = cl.find(delim,spos);
		curr_tfe.feature_id = cl.substr(spos,epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.type = cl.substr(spos,epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.location = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.start = std::stoi(cl.substr(spos, epos));
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.stop = std::stoi(cl.substr(spos, epos));
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.strand = cl.substr(spos,epos)=="+" ? true : false;
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.function = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.aliases = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.figfam = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.evidence_codes = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.nucleotide_sequence = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		epos = cl.find(delim, spos);
		curr_tfe.aa_sequence = cl.substr(spos, epos);
		cl.erase(0, epos+delim.size());

		res.data.push_back(curr_tfe);
	}

	return res; // {false,"true"};
}


bool check_tablefile(const tablefile& tf) {
	
	for (const auto& e : tf.data) {
		if (std::abs(e.stop-e.start)+1 != e.nucleotide_sequence.size()) {
			// [e.start,e.stop], not [e.start,e.stop)
			return false;
		}

		if ((e.stop<e.start && e.strand) || (e.stop>e.start && !e.strand)) {
			// Though in theory an element could span the nt defined as 0 and still be
			// on the + strand...
			return false;
		}

		bool is_protein {e.type.find("peg")!=std::string::npos};
		bool is_rna {e.type.find("rna")!=std::string::npos};
		if ((is_protein && is_rna) || (!is_protein && !is_rna)) {
			return false;
		}
		if (is_rna) {
			if (e.aa_sequence.size() != 0) {
				return false;
			}
		}

		if (is_protein) {
			if (e.nucleotide_sequence.size()%3 != 0) {
				return false;
			}

			if (e.aa_sequence.size()*3+3 != e.nucleotide_sequence.size()) {
				return false;
			}
		}
	}

	return true;
}

