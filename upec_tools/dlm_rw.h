#pragma once
#include <vector>
#include <string>
#include <filesystem>

struct dlmread_opts {
	std::string expected_header {};
	bool fail_if_no_header {false};
	int expected_ncol {0};
	bool fail_if_wrong_ncol {false};  // If any line has thw wrong ncols, fail
};
std::vector<std::vector<std::string>> dlmread(const std::filesystem::path&, const std::string&);

//
// At this point, does nothing more than allows addressing of cols by name
// rather than by numeric idx.  
//
class table {
public:
	table()=default;
	table(const std::vector<std::vector<std::string>>&, bool);
	std::vector<std::string> row(int) const;
	std::vector<std::string> col(int) const;
	std::vector<std::string> col(const std::string&) const;
	std::string cell(int, const std::string&) const;

	table subtable(const std::vector<int>&) const;  // rows
private:
	int cname2cidx(const std::string& cname) const;

	int m_nr {0};
	std::vector<std::string> m_ch {};
	std::vector<std::vector<std::string>> m_data {};  // m_data[col][row]
	// In a future, templated version, expect each col to have the same type, 
	// hence the inner vector(s) should be the row(s).  
};



