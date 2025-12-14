#include <BitcoinExchange.hpp>

// Constructors
BitcoinExchange::BitcoinExchange( void ) {

	_readDatabase();

}

BitcoinExchange::BitcoinExchange( BitcoinExchange const &other ) {

	if ( this != &other )
		*this = other;

}

BitcoinExchange &BitcoinExchange::operator=( BitcoinExchange const &other ) {

	if ( this != &other )
		_quotes = other._quotes;

	return ( *this );

}

BitcoinExchange::~BitcoinExchange( void ) {
}

// Getters
std::map<std::string, double> const &BitcoinExchange::getQuotes( void ) const {

    return ( _quotes );

}

void BitcoinExchange::_readDatabase( void ) {

       std::ifstream file( "data.csv" );

        if ( !file.is_open() )
            throw CouldNotOpenFile();

        std::string line;

        std::getline( file, line );

        if ( line != "date,exchange_rate" )
            throw InvalidColumnFormat();

        while ( std::getline( file, line ) ) {

            std::string date, price;
            std::istringstream ss( line );
            std::getline( ss, date, ',' );
            std::getline( ss, price, ',' );
            double priceValue;
            std::istringstream priceStream( price );

            if ( !( priceStream >> priceValue ) )
				throw InvalidPriceFormat();
            _quotes[ date ] = priceValue;

        }

        file.close();

}

void BitcoinExchange::execute( char const *fileName ) {

	std::ifstream file( fileName );

	if ( !file.is_open() )
		throw CouldNotOpenFile();

	std::string line;

	std::getline( file, line );

	if ( line != "date | value" )
		throw InvalidColumnFormat();

	while ( std::getline( file, line ) ) {

		std::string date;
		std::string valueStr;
		double priceValue;
		std::istringstream ss( line );
		std::getline( ss, date, '|' );
		std::getline( ss, valueStr, '|' );

		if ( !date.empty() )
			date = date.erase( date.length() - 1 );

		if ( _validateDate( date ) == false ) {

			std::cout << "Error: bad input => " << date << std::endl;
			continue;

		}

		if( !valueStr.empty() )
			valueStr = valueStr.erase( 0, 1 );

		priceValue = _validatePrice( valueStr );

		if ( priceValue != -1 )
			_multiplyWithQuote( date, priceValue );
		
	}

	file.close();

}

bool BitcoinExchange::_validateDate( std::string const &date ) {

	if ( date.size() != 10 || date[ 4 ] != '-' || date[ 7 ] != '-' )
		return ( false );

	for ( int i = 0; i < 10; i++ ) {
		if ( i == 4 || i == 7 )
			continue;
		if ( !isdigit( date[ i ] ) )
			return ( false );
	}

	int year  = std::atoi( date.substr( 0, 4 ).c_str() );
    int month = std::atoi( date.substr( 5, 2 ).c_str() );
    int day   = std::atoi( date.substr( 8, 2 ).c_str() );

    if (month < 1 || month > 12)
        return ( false  );

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeap = ( year % 4 == 0 && year % 100 != 0 ) || ( year % 400 == 0 );

    if ( month == 2 && isLeap )
        daysInMonth[ 1 ] = 29;

    if ( day < 1 || day > daysInMonth[ month - 1 ] )
        return ( false  );

    return ( true  );

}

double BitcoinExchange::_validatePrice( std::string const &valueStr ) {

	double priceValue;
	std::istringstream priceStream( valueStr );

	if ( !( priceStream >> priceValue ) || !priceStream.eof() ) {
		std::cout << "Error: bad value input => " << valueStr << std::endl;
		return ( -1 );
	}

	if ( priceValue < 0 ) {
		std::cout << "Error: not a positive number => " << priceValue << std::endl;
		return ( -1 );
	}
	else if ( priceValue > 1000 ) {
		std::cout << "Error: too large number => " << priceValue << std::endl;
		return ( -1 );
	}
	
	return ( priceValue );

}

void BitcoinExchange::_multiplyWithQuote( std::string const &date, double price ) {

	std::map< std::string, double >::iterator it = _quotes.find( date );

	if ( it != _quotes.end() )
		std::cout << date << " | " << price << " | " << price * it->second << std::endl;
	else {

		std::map< std::string, double >::iterator it2 = _quotes.lower_bound( date );

		if ( it2 == _quotes.begin() )
			std::cout << date << " | " << price << " | " << price * it2->second << std::endl;
		else {
			it2--;
			std::cout << date << " | " << price << " | " << price * it2->second << std::endl;
		}
	}

}