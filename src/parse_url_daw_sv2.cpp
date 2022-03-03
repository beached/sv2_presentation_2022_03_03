// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/sv2_presentation_2022_03_03
//

#include <daw/daw_string_view.h>

struct uri_parts {
	daw::string_view scheme;
	daw::string_view authority;
	daw::string_view path;
	daw::string_view query;
	daw::string_view fragment;
};

// scheme://authority:port/path/?query#fragment
constexpr uri_parts parse_url( daw::string_view uri_string ) {
	return { .scheme = uri_string.pop_front_until( "://" ),
	         .authority = uri_string.pop_front_until( daw::any_of<'/', '?', '#'>,
	                                                  daw::nodiscard ),
	         .path = uri_string.pop_front_until( daw::any_of<'?', '#'> ),
	         .query = uri_string.pop_front_until( '#' ),
	         .fragment = uri_string };
}

int main( ) {
	constexpr uri_parts p0 = parse_url( "http://www.google.ca" );
	static_assert( p0.scheme == "http" );
	static_assert( p0.authority == "www.google.ca" );
	static_assert( p0.path.empty( ) );
	static_assert( p0.query.empty( ) );
	static_assert( p0.fragment.empty( ) );

	constexpr uri_parts p1 = parse_url( "http://www.google.ca/search?q=string_view" );
	static_assert( p1.scheme == "http" );
	static_assert( p1.authority == "www.google.ca" );
	static_assert( p1.path == "/search" );
	static_assert( p1.query == "q=string_view" );
	static_assert( p1.fragment.empty( ) );
}
