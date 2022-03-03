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
	std::string_view sv = "This is a test  of the test system   ";

	while( not sv.empty( ) ) {
		auto pos = sv.find_first_of( ' ' );
		if( pos == std::string_view::npos ) {
			std::cout << '"' << sv << '"' << '\n';
			break;
		}
		std::cout << '"' << sv.substr( 0, pos ) << '"' << '\n';
		auto pos2 = sv.find_first_not_of( ' ', pos );
		if( pos2 == std::string_view::npos ) {
			break;
		}
		sv.remove_prefix( pos2 );
	}
}