// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/sv2_presentation_2022_03_03
//

#include <daw/daw_string_view.h>

#include <iostream>

int main( ) {
	daw::string_view sv = "This is a test  of the test system   ";
	while( not sv.empty( ) ) {
		auto part = sv.pop_front_until( ' ' );
		std::cout << '"' << part << '"' << '\n';
	}
}
