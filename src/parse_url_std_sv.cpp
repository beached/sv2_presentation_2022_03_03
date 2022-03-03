// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/sv2_presentation_2022_03_03
//

// Demonstrate a conventional string_view based function to convert a
// string_view into it's URI parts

#include <cassert>
#include <string_view>

struct uri_parts {
	std::string_view scheme;
	std::string_view authority;
	std::string_view path;
	std::string_view query;
	std::string_view fragment;
};

// scheme://authority:port/path/?query#fragment
constexpr uri_parts parse_url( std::string_view uri_string ) {
	auto result = uri_parts{ };
	auto pos = uri_string.find_first_of( "://" );
	if( pos == std::string_view::npos ) {
		result.scheme = uri_string;
		return result;
	}
	result.scheme = uri_string.substr( 0, pos );
	uri_string.remove_prefix( pos );
	// Need to check, UB to remove_prefix if size( ) < 3
	if( uri_string.size( ) <= 3 ) {
		return result;
	}
	uri_string.remove_prefix( 3 );
	auto it = std::find_if( uri_string.begin( ), uri_string.end( ), []( char c ) {
		return c == '/' or c == '?' or c == '#';
	} );
	pos = std::distance( uri_string.begin( ), it );
	result.authority = uri_string.substr( 0, pos );
	uri_string.remove_prefix( pos );
	it = std::find_if( uri_string.begin( ), uri_string.end( ),
	                   []( char c ) { return c == '?' or c == '#'; } );
	pos = std::distance( uri_string.begin( ), it );
	result.path = uri_string.substr( 0, pos );
	uri_string.remove_prefix( pos );
	// Need to check, UB to remove_prefix if size( ) < 1
	if( uri_string.empty( ) ) {
		return result;
	}
	uri_string.remove_prefix( 1 );
	pos = uri_string.find( '#' );
	if( pos != std::string_view::npos ) {
		result.query = uri_string.substr( 0, pos );
		uri_string.remove_prefix( pos );
		// Need to check, UB to remove_prefix if size( ) < 1
		if( not uri_string.empty( ) ) {
			uri_string.remove_prefix( 1 );
		}
	}
	result.fragment = uri_string;
	return result;
}

int main( ) {
	constexpr uri_parts p0 = parse_url( "http://www.google.ca" );
	static_assert( p0.scheme == "http" );
	static_assert( p0.authority == "www.google.ca" );
	static_assert( p0.path.empty( ) );
	static_assert( p0.query.empty( ) );
	static_assert( p0.fragment.empty( ) );

	constexpr uri_parts p1 =
	  parse_url( "http://www.fun.com/joke?q=knock+knock#whos+there" );
	static_assert( p1.scheme == "http" );
	static_assert( p1.authority == "www.fun.com" );
	static_assert( p1.path == "/joke" );
	static_assert( p1.query == "q=knock+knock" );
	static_assert( p1.fragment == "whos+there" );
}
