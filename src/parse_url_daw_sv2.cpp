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
	auto result = uri_parts{ };
	result.scheme = uri_string.pop_front_until( "://" );
	result.authority =
	  uri_string.pop_front_until( daw::any_of<'/', '?', '#'>, daw::nodiscard );
	result.path =
	  uri_string.pop_front_until( daw::any_of<'?', '#'>, daw::nodiscard );
	if( uri_string.empty( ) ) {
		return result;
	}
	if( uri_string.front( ) == '?' ) {
		uri_string.remove_prefix( );
		result.query = uri_string.pop_front_until( '#' );
	}
	if( not uri_string.empty( ) and uri_string.front( ) == '#' ) {
		uri_string.remove_prefix( );
	}
	result.fragment = uri_string;
	return result;
}

int main( ) {
	constexpr uri_parts p0 = parse_url( "https://www.google.ca" );
	static_assert( p0.scheme == "https" );
	static_assert( p0.authority == "www.google.ca" );
	static_assert( p0.path.empty( ) );
	static_assert( p0.query.empty( ) );
	static_assert( p0.fragment.empty( ) );

	constexpr uri_parts p1 =
	  parse_url( "https://www.example.com/joke?q=knock+knock" );
	static_assert( p1.scheme == "https" );
	static_assert( p1.authority == "www.example.com" );
	static_assert( p1.path == "/joke" );
	static_assert( p1.query == "q=knock+knock" );
	static_assert( p1.fragment.empty( ) );

	constexpr uri_parts p2 = parse_url( "https://www.example.com/#stuff" );
	static_assert( p2.scheme == "https" );
	static_assert( p2.authority == "www.example.com" );
	static_assert( p2.path == "/" );
	static_assert( p2.query.empty( ) );
	static_assert( p2.fragment == "stuff" );
}
