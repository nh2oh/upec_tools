#include "tablefile.h"
#include "fasta_genome.h"
#include "strutils.h"
#include "dlm_rw.h"
#include <iostream>
#include <vector>
#include <string>


int main() {
	
	auto br21 = dlmread("..\\tables\\UTI12_BlstResult.txt","\t");
	table t_br21 {br21,true};

	std::string file_uti21 {"..\\tables\\UTI21_table.txt"};
	auto uti21 = read_tablefile(file_uti21);
	//auto uti21_is_valid = check_tablefile(uti21);
	auto tfs21 = calc_tablefilestats(uti21);
	std::cout << tfs21.num_prot << "\n" << tfs21.num_rna << "\n" << tfs21.mean_len_prot << "\n" << tfs21.mean_len_rna << std::endl;
	//std::string file_uti21_fasta {"..\\tables\\UTI21_fastaprot.txt"};
	//auto x= tablefile2fastafile(uti21,file_uti21_fasta);

	auto dbki21 = annotate_dbk_interest("..\\tables\\UTI12_of_interest.txt", uti21);

	std::string s {};
	for (const auto& e : dbki21) {
		if (e.function != "") {
			s += e.name + "\t" + e.function + "\n";
		}
	}
	std::cout << s << std::endl;

	std::string file_uti12 {"..\\tables\\UTI12_table.txt"};
	auto uti12 = read_tablefile(file_uti12);
	auto tfs12 = calc_tablefilestats(uti12);
	std::cout << tfs12.num_prot << "\n" << tfs12.num_rna << "\n" << tfs12.mean_len_prot << "\n" << tfs12.mean_len_rna << std::endl;







	//std::string file_cft073g {"..\\tables\\GCA_000007445.1_ASM744v1_genomic.fna"};
	//auto cft073genome = read_fgfile(file_cft073g);
	//std::string file_cft073cds {"..\\tables\\GCA_000007445.1_ASM744v1_cds_from_genomic.fna"};
	//auto cft073cds = read_fastafile(file_cft073cds);

	//std::string h = ">lcl|AE014075.1_cds_AAN78503.1_3 [gene=thrA] [locus_tag=c0003] [protein=Aspartokinase I] [protein_id=AAN78503.1] [location=985..3510] [gbkey=CDS]";
	//auto hf = strfields(h,"[","]");

	//auto thra_seq_genome = cft073genome.seq.substr(985-1,(3510-985+1));
	//auto thra_seq_cds = cft073cds.data[2].seq;

	//bool yesno = (thra_seq_genome==thra_seq_cds);

	return 0;
}

