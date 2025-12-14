#include <PmergeMe.hpp>

void print_arguments( char **argv ) {

	int i = 1;
	int error = 0;

	std::cout << "Before: ";

	while ( argv[ i ] ) {

		std::string input = argv[ i ];
		std::cout << input << " ";

		if ( input.size() > 10 || std::atol( input.c_str() ) > INT_MAX || std::atol( input.c_str() ) < 0 )
			error = 1;

		for ( size_t j = 0; j < input.size(); j++ ) {

			if ( !isdigit( input[ j ] ) )
				error = 1;

		}
		i++;

	}

	std::cout << "\n";

	if ( error == 1 )
		throw CustomException( "Error: input is invalid" );

}

long jacobsthal_number( int n ) {
	return ( round( ( pow( 2, n ) - pow( -1, n ) ) / 3 ) );
}