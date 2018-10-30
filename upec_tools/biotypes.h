#pragma once
#include <string>
#include <array>

class amino_acid {
public:
	explicit amino_acid()=default;
	explicit amino_acid(const std::string&);

	enum aa_print_mode {
		one,
		three,
		full
	};
	std::string to_str(aa_print_mode=one) const;  // 1 => 1-letter, 3=>3-letter
private:
	char m_aa_val {0};

	struct aa_map {
		std::array<char,2> one_letter {"A"};
		std::array<char,4> three_letter {"ALA"};
		std::array<char,14> three_letter {"Alanine"};
	};

	static const std::array<aa_map,2> m_map;
	//static const std::array<char,20> one_letter_codes;
	//static const std::array<char,20> three_letter_codes;
	//static const std::array<char,20> names;
};




