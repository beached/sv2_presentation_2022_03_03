// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/sv2_presentation_2022_03_03
//

// Demonstrate a conventional string_view based function to convert a
// string_view into it's URI parts

#include <iostream>
#include <string_view>

int main( ) {
	std::string_view sv = "   This is a test  of the test system   ";
	auto pos = sv.find_first_not_of( ' ' );
	// npos checking
	if( pos != std::string_view::npos ) {
		sv.remove_prefix( pos );
	}
	pos = sv.find_last_not_of( ' ' );
	if( pos != std::string_view::npos ) {
		// Easy off by 1
		sv.remove_suffix( sv.size( ) - pos - 1 );
	}
	std::cout << '"' << sv << '"' << '\n';
}