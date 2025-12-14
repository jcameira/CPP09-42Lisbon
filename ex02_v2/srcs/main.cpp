#include <PmergeMe.hpp>

int	main( int argc, char **argv )
{
	if ( argc < 2 )
		return ( std::cerr << "Not enough arguments provided\n", 1 );

    try {
        print_arguments( argv );
    }
    catch( const std::exception& e ) {
        std::cerr << e.what() << '\n';
    }

    std::vector<int> vec = fill_container< std::vector<int> >( argc, argv );
    clock_t start_vec = clock();
    merge_insertion_sort( vec, 1 );
    clock_t end_vec = clock();
    print_container( vec );

    std::deque<int> deque = fill_container< std::deque<int> >( argc, argv );
    clock_t start_deque = clock();
    merge_insertion_sort( deque, 1 );
    clock_t end_deque = clock();
    //print_container( deque );

    std::list<int> list = fill_container< std::list<int> >( argc, argv );
    clock_t start_list = clock();
    merge_insertion_sort( list, 1 );
    clock_t end_list = clock();
    //print_container( list );

    if ( !is_sorted( vec ) || static_cast<int>( vec.size() ) != ( argc - 1 ) ) {
        std::cout << "Vector was not sorted properly.\n";
		return ( 1 );
	}
    if ( !is_sorted( deque ) || static_cast<int>( deque.size() ) != ( argc - 1 ) ) {
        std::cout << "Deque was not sorted properly.\n";
		return ( 1 );
	}
    if ( !is_sorted( list ) || static_cast<int>( list.size() ) != ( argc - 1 ) ) {
        std::cout << "List was not sorted properly.\n";
		return ( 1 );
	}

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector: " << std::fixed << std::setprecision( 6 )
              << static_cast<double>( end_vec - start_vec ) / CLOCKS_PER_SEC << "s\n";
    std::cout << "Time to process a range of " << deque.size()
              << " elements with std::deque:  " << std::fixed << std::setprecision( 6 )
              << static_cast<double>( end_deque - start_deque ) / CLOCKS_PER_SEC << "s\n";
    std::cout << "Time to process a range of " << list.size()
              << " elements with std::list:  " << std::fixed << std::setprecision( 6 )
              << static_cast<double>( end_list - start_list ) / CLOCKS_PER_SEC << "s\n";

    return ( 0 );
}