#include "dlm_rw.h"
#include "strutils.h"
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>


table::table(const std::vector<std::vector<std::string>>& t, bool has_headers) {
	if (t.size() == 0) {
		std::cout << "No table data:  t.size() == 0";
		std::abort();
	}
	m_nr = t[0].size();

	if (has_headers && t.size() >= 1) {
		m_ch = t[0];
	}
	
	int idx_start = has_headers ? 1 : 0;
	for (int i=idx_start; i<t.size(); ++i) {
		if (t[i].size() != m_nr) {
			std::cout << "Row i=" << i << " has " << t[i].size() << " rows; nr=" << m_nr << " expected.  ";
			std::abort();
		}
		m_data.push_back(t[i]);  // TODO:  Preallocate m_data
	}
}

std::vector<std::string> table::row(int ridx) const {
	if (ridx > m_nr) {
		std::cout << "requested row ridx=" << ridx << " exceeds table dimensions.";
		std::abort();
	}
	std::vector<std::string> res {};  res.reserve(m_nr);
	for (const auto& c : m_data) {
		res.push_back(c[ridx]);
	}
	return res;
};
table table::subtable(const std::vector<int>& ridxs) const {  // rows
	auto it = std::find_if(ridxs.begin(),ridxs.end(),[&](const int& ridx){ return ridx>m_nr;});
	if (it != ridxs.end()) {
		std::cout << "At least one requested ridx exceeds table dimensions.";
		std::abort();
	}
	table res {};
	res.m_ch = m_ch;
	res.m_nr = ridxs.size();

	for (int cidx=0; cidx<m_data.size(); ++cidx) {  // TODO:  This could be a range-for
		std::vector<std::string> curr_col {};
		for (const auto& ridx : ridxs) {
			curr_col.push_back(m_data[cidx][ridx]);
		}
		res.m_data.push_back(curr_col);
	}

	return res;
}
std::vector<std::string> table::col(int cidx) const {
	if (cidx > m_data.size()) {
		std::cout << "requested col cidx=" << cidx << " exceeds table dimensions.";
		std::abort();
	}
	return m_data[cidx];
};
std::vector<std::string> table::col(const std::string& cname) const {
	int cidx = cname2cidx(cname);
	return m_data[cidx];
};
std::string table::cell(int ridx, const std::string& cname) const {
	int cidx = cname2cidx(cname);
	std::vector<std::string> r = row(ridx);
	return r[cidx];
}

int table::cname2cidx(const std::string& cname) const {
	auto it = std::find(m_ch.begin,m_ch.end,cname);
	if (it == m_ch.end()) {
		std::cout << "requested col cname=\"" << cname << "\" does not exist.";
		std::abort();
	}

	return (it-m_ch.begin());
};



std::vector<std::vector<std::string>> dlmread(const std::filesystem::path& fp, const std::string& delim) {
	std::fstream fs {fp,std::ios::in};
	if (!fs.is_open() || fs.fail()) {
		std::cout << "Error opening file:  " << std::filesystem::absolute(fp) << std::endl;
		std::abort();
	}
	
	std::string cl {};
	int curr_line_num {0};
	while (!fs.eof()) {
		++curr_line_num;
		std::getline(fs,cl);
		if (cl.size() == 0) {
			continue;
		};

		auto curr_tks = strtok(cl,delim);

		cl.clear();
	}

	std::vector<std::vector<std::string>> res {};

	return res;
}









