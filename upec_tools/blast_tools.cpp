#include<string>



std::string print_commands() {
	std::string s {};


	/*
	User supplied sequences should make use of the local or general identifiers described in:
	http://www.ncbi.nlm.nih.gov/toolkit/doc/book/ch_demo/#ch_demo.T5
	Ex:
	$ cat mydb.fsa
	>gnl|MYDB|1 this is sequence 1
	GAATTCCCGCTACAGGGGGGGCCTGAGGCACTGCAGAAAGTGGGCCTGAGCCTCGAGGATGACGGTGCTGCAGGAACCCG
	>gnl|MYDB|2 this is sequence 2
	TCCAGGCTGCTATATGGCAAGCACTAAACCACTATGCTTACCGAGATGCGGTTTTCCTCGCAGAACGCCTTTATGCAGAA
	
	$ makeblastdb -in mydb.fsa -parse_seqids -dbtype nucl

	All entries are part of the “MYDB” database, with the entries numbers 1, 2, and 3.  
	Makeblastdb will store this information properly and produce an index, so that the 
	sequences can be retrieved by these identifiers. Makeblastdb stores the title portion
	of the definition line (e.g., “this is sequence 1”), but will not parse it. If the 
	first token after the “>” does not contain a bar (“|”) it will be parsed as a local 
	ID. Use the full identifier string (e.g., “gnl|MYDB|2”) to retrieve sequences with 
	a general ID.  
	General:  gnl\|database\|string
	Local:  lcl\|string
	Genbank:  gb\|accession\|locus
	Refseq:  ref\|accession\|locus

	makeblastdb.exe
	-in ..\..\git\upec_tools\tables\strains\cft073\GCF_000007445.1_ASM744v1_protein.faa
	-input_type fasta
	-dbtype prot
	-parse_seqids
	-logfile ..\..\git\upec_tools\tables\strains\cft073\GCF_000007445.1_ASM744v1_protein_bdb_log.txt
	-out ..\..\git\upec_tools\tables\strains\cft073\GCF_000007445.1_ASM744v1_protein_bdb

	makeblastdb.exe -in ..\..\git\upec_tools\tables\strains\uti89\GCF_000013265.1_ASM1326v1_protein.faa -input_type fasta -dbtype prot -parse_seqids -logfile ..\..\git\upec_tools\tables\strains\uti89\GCF_000013265.1_ASM1326v1_protein_bdb_log.txt -out ..\..\git\upec_tools\tables\strains\uti89\GCF_000013265.1_ASM1326v1_protein_bdb




	blastp.exe
	-db ..\..\git\upec_tools\tables\strains\uti89\GCF_000013265.1_ASM1326v1_protein_bdb
	-out ..\..\git\upec_tools\tables\testq\testy_BlstResult.txt ', ...
	-query ..\..\git\upec_tools\tables\testq\testy_q.faa
	-num_threads 1
	-outfmt 10
	-max_target_seqs 5


	blastp.exe
	-db ..\blast_dbs\GCF_000013265.1_ASM1326v1_protein_bdb
	-out ..\UTI12_BlstResult.txt 
	-query ..\UTI12_fastaprot.txt
	-num_threads 4
	-max_target_seqs 5
	-outfmt "6 qacc sacc qstart qend qlen sstart send slen evalue bitscore score pident"

	blastp.exe -db ..\blast_dbs\GCF_000013265.1_ASM1326v1_protein_bdb -out ..\UTI12_BlstResult.txt -query ..\UTI12_fastaprot.txt -num_threads 4 -max_target_seqs 5 -outfmt "6 qacc sacc qstart qend qlen sstart send slen evalue bitscore score pident"




	*/

	std::string makeblastdb = "makeblastdb.exe -in uti12_p.fsa -input_type fasta -dbtype prot -parse_seqids ";
	makeblastdb += "-logfile makeblastdb_log.txt -out bdb_name";



	return s;
}


