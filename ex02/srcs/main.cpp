#include "PmergeMe.hpp"


int	main( int argc, char **argv )
{
	if ( argc < 2 )
		return ( std::cerr << "Not enough arguments provided\n", 1 );
	
	// first approach: std::list
	{
        
		std::cout << "using std::list" << std::endl;
		clock_t start = clock();
		std::list< std::pair< int, int > > listy;
		std::list< int > main_chain;
		int additional_value = -1;
		
		try {

			print_before( argv );
			create_pairs( &listy, argv, &additional_value );
			sort_pairs( &listy );
			mergeSort( listy.begin(), listy.end(), 0 );
            init_main_chain( &main_chain, listy );
            insert_into_main_chain( listy, &main_chain, additional_value );
			print_after( main_chain );
			
			clock_t end = clock();
			std::cout << "Time to process a range of " << main_chain.size() << " elements with std::list: " << static_cast< double >( end - start ) / 1000 << " millisec" << std::endl << std::endl;

		}
		catch( const std::exception& e ) {

			std::cerr << e.what() << '\n';

		}
        
	}

	// second approach: std::deque
	{
        
		std::cout << "using std::deque" << std::endl;
		clock_t start = clock();
		std::deque< std::pair< int, int > > dequey;
		std::deque< int > main_chain;
		int additional_value = -1;

		try {

			print_before( argv );
			create_pairs2( &dequey, argv, &additional_value );
			sort_pairs2( &dequey );
			mergeSort2( dequey.begin(), dequey.end(), 0 );
			init_main_chain2( &main_chain, dequey );
			insert_into_main_chain2( dequey, &main_chain, additional_value );
			print_after2( main_chain );
			
			clock_t end = clock();
			std::cout << "Time to process a range of " << main_chain.size() << " elements with std::deque: " << static_cast< double >( end - start ) / 1000 << " millisec" << std::endl;

		}
		catch( const std::exception& e ) {

			std::cerr << e.what() << '\n';

		}
        
	}

	return ( 0 );

}