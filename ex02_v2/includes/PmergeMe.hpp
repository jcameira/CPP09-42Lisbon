#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <deque>
# include <vector>
# include <string>
# include <iostream>
# include <utility>
# include <algorithm>
# include <climits>
# include <cmath>
# include <iomanip>

class CustomException : public std::runtime_error
{
	public:
		explicit CustomException(std::string msg): runtime_error(msg) {}
};

void    print_arguments( char **argv );

long    jacobsthal_number( int n );

template <typename T>
T fill_container( int argc, char** argv )
{
    T container;
    for ( int i = 1; i < argc; i++) {
        container.push_back( std::atoi( argv[ i ] ) );
    }
    return ( container );
}

template <typename T>
void print_container( T &container )
{
    for ( typename T::iterator it = container.begin(); it != container.end(); it++ ) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
static bool is_sorted( const T& container )
{
    if ( container.size() == 0 || container.size() == 1 )
        return ( true );
    typename T::const_iterator end = container.end();
    end--;
    for ( typename T::const_iterator it = container.begin(); it != end; it++ ) {
        typename T::const_iterator next = it;
        next++;
        if ( *it > *next )
            return ( false );
    }
    return ( true );
}

template <typename T>
T advance_iterator_by_n( T it, int steps ) {
    std::advance( it, steps );
    return ( it );
}

template <typename T>
bool comparison(T lv, T rv) {
	return ( *lv < *rv );
}

template <typename T>
void merge_insertion_sort( T &container, int pair_level ) {

    int pair_units_nbr = container.size() / pair_level;

    if ( pair_units_nbr < 2 )
        return ;
    
    bool is_odd = pair_units_nbr % 2 == 1;

    typename T::iterator start = container.begin();
    typename T::iterator end = advance_iterator_by_n( start, ( pair_level * pair_units_nbr ) - ( is_odd * pair_level ) );

    int elements_per_pair = pair_level * 2;

    for ( typename T::iterator it = start; it != end; it = advance_iterator_by_n( it, elements_per_pair ) ) {
        typename T::iterator first_element_end = advance_iterator_by_n( it, pair_level - 1 );
        typename T::iterator second_element_end = advance_iterator_by_n( it, pair_level * 2 - 1 );

        if ( *second_element_end < *first_element_end ) {
            typename T::iterator first_element_start = advance_iterator_by_n( first_element_end, 1 - pair_level );
            typename T::iterator second_element_start = advance_iterator_by_n( first_element_start, pair_level );
            while ( first_element_start != second_element_start ) {
                std::iter_swap( first_element_start, advance_iterator_by_n( first_element_start, pair_level ) );
                first_element_start++;
            }
        }
    }

    merge_insertion_sort( container, pair_level * 2 );

    std::vector<typename T::iterator> main;
    std::vector<typename T::iterator> pend;

    main.insert( main.end(), advance_iterator_by_n( container.begin(), pair_level - 1 ) );
    main.insert( main.end(), advance_iterator_by_n( container.begin(), ( pair_level * 2 ) - 1 ) );

    for ( int i = 4; i <= pair_units_nbr; i += 2 ) {
        pend.insert( pend.end(), advance_iterator_by_n( container.begin(), ( pair_level * ( i - 1 ) ) - 1 ) );
        main.insert( main.end(), advance_iterator_by_n( container.begin(), ( pair_level * i ) - 1 ) );
    }

    if ( is_odd )
        pend.insert( pend.end(), advance_iterator_by_n( end, pair_level - 1 ) );
    
    int prev_jacobsthal_number = jacobsthal_number( 2 );
    int inserted_elements = 0;
    for ( int i = 3;;i++ ) {
        int curr_jacobsthal_number = jacobsthal_number( i );
        int jacobsthal_diff = curr_jacobsthal_number - prev_jacobsthal_number;
        int offset = 0;

        if ( jacobsthal_diff > static_cast<int>( pend.size() ) )
            break;
        
        int elements_to_insert = jacobsthal_diff;
        typename std::vector<typename T::iterator>::iterator pend_it = advance_iterator_by_n( pend.begin(), elements_to_insert - 1 );
        typename std::vector<typename T::iterator>::iterator bound_it = advance_iterator_by_n( main.begin(), curr_jacobsthal_number + inserted_elements );

        while ( elements_to_insert ){
            typename std::vector<typename T::iterator>::iterator idx = std::upper_bound( main.begin(), bound_it, *pend_it, comparison<typename T::iterator> );
            typename std::vector<typename T::iterator>::iterator inserted = main.insert( idx, *pend_it );
            elements_to_insert--;
            pend_it = pend.erase(pend_it);
            pend_it--;

            if ( inserted - main.begin() == curr_jacobsthal_number + inserted_elements )
                offset++;

            bound_it = advance_iterator_by_n(main.begin(), curr_jacobsthal_number + inserted_elements - offset);
        }

        prev_jacobsthal_number = curr_jacobsthal_number;
        inserted_elements += jacobsthal_diff;
		offset = 0;

    }

    for ( int i = pend.size() - 1; i >= 0; i-- ) {
        typename std::vector<typename T::iterator>::iterator curr_pend = advance_iterator_by_n( pend.begin(), i );
        typename std::vector<typename T::iterator>::iterator curr_bound = advance_iterator_by_n( main.begin(), main.size() - pend.size() + i + is_odd );
        typename std::vector<typename T::iterator>::iterator idx = std::upper_bound( main.begin(), curr_bound, *curr_pend, comparison<typename T::iterator> );
        main.insert( idx, *curr_pend );
    }

    std::vector<int> copy;
    for ( typename std::vector<typename T::iterator>::iterator it = main.begin(); it != main.end(); it++ ) {
        for (int i = 0; i < pair_level; i++) {
            typename T::iterator pair_start = *it;
            std::advance (pair_start, -pair_level + i + 1 );
            copy.insert( copy.end(), *pair_start );
        }
    }

    typename T::iterator container_it = container.begin();
    std::vector<int>::iterator copy_it = copy.begin();
    while ( copy_it != copy.end() ) {
        *container_it = *copy_it;
        container_it++;
        copy_it++;
    }
}

#endif