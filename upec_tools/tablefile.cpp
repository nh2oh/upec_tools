#include "tablefile.h"
#include "strutils.h"
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
	
	std::string delim {"\t"};
	int expect_n_fields {13};

	std::string cl {};  // "current line"
	std::string expect_header{"contig_id	feature_id	type	location	start	stop	strand	function	aliases	figfam	evidence_codes	nucleotide_sequence	aa_sequence"};
	int curr_line_num {1};
	std::getline(fs, cl);  // The first line must eb the expected col headers
	if (cl != expect_header) {
		std::cout << "Error reading header" << std::endl;
		std::abort();
	}
	while (!fs.eof()) {
		++curr_line_num;
		std::getline(fs,cl);
		if (cl.size() == 0) {
			continue;
		};

		tablefile_entry curr_tfe {};
		auto vs = strtok(cl,delim);
		if (vs.size() != expect_n_fields) {
			std::cout << "Error reading line " << curr_line_num << ": \n"
				<< cl << "\n" << "Expected " << expect_n_fields << " but "
				<< "found " << vs.size() << std::endl;
			std::abort();
		}
		curr_tfe.contig_id = vs[0];
		curr_tfe.feature_id = vs[1];
		curr_tfe.type = vs[2];
		curr_tfe.location = vs[3];
		curr_tfe.start = std::stoi( vs[4]);
		curr_tfe.stop = std::stoi( vs[5]);
		curr_tfe.strand = vs[6]=="+" ? true : false;
		curr_tfe.function =  vs[7];
		curr_tfe.aliases =  vs[8];
		curr_tfe.figfam =  vs[9];
		curr_tfe.evidence_codes =  vs[10];
		curr_tfe.nucleotide_sequence =  vs[11];
		curr_tfe.aa_sequence =  vs[12];

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



std::string tablefile2fastafile(const tablefile& tf, const std::filesystem::path& ffp) {
	std::string ff_contents {};

	for (const auto& e : tf.data) {
		//ff_contents += ">";
		//ff_contents += e.contig_id + " " + e.feature_id + " ";
		//ff_contents += "start=[" + std::to_string(e.start) + "] ";
		//ff_contents += "stop=[" + std::to_string(e.stop) + "] ";
		//ff_contents += "aliases=[" + e.aliases + "] ";
		//ff_contents += "figfam=[" + e.figfam + "] ";
		//ff_contents += "\n";
		//ff_contents += e.aa_sequence;
		//ff_contents += "\n\n";

		ff_contents += ">";
		ff_contents += e.location;
		//ff_contents += e.contig_id + " " + e.feature_id + " ";
		//ff_contents += "start=[" + std::to_string(e.start) + "] ";
		//ff_contents += "stop=[" + std::to_string(e.stop) + "] ";
		//ff_contents += "aliases=[" + e.aliases + "] ";
		//ff_contents += "figfam=[" + e.figfam + "] ";
		ff_contents += "\n";
		ff_contents += e.aa_sequence;
		ff_contents += "\n\n";


	}

	std::fstream ff {ffp,std::ios::out};
	ff << ff_contents;
	return "yay";
	ff.close();
}




