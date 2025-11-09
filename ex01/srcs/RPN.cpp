#include <RPN.hpp>

//Constructors
RPN::RPN( void ) {
}

RPN::RPN( const std::string &inputStr ) {

	std::stringstream ss( inputStr );
	std::string token;
	int num;

	while ( std::getline( ss, token, ' ' ) ) {

		if ( ( token.length() == 1 && isdigit( token[ 0 ] ) ) || ( token.length() == 2 && token[ 0 ] == '-' && isdigit( token[ 1 ] ) ) )
		{
			std::stringstream( token ) >> num;
			_stack.push( num );
		}
		else if ( token == "+" )
			_executeStack( &RPN::_plus );
		else if (token == "-")
			_executeStack( &RPN::_minus );
		else if (token == "*")
			_executeStack( &RPN::_multiply );
		else if (token == "/")
			_executeStack( &RPN::_divide );
		else
			throw RPN::invalidArgument( "Invalid argument: " + token );

	}

}

RPN::RPN( const RPN &other ) {

	*this = other;

}

RPN &RPN::operator=( const RPN &other ) {

	if ( this != &other )
		_stack = other._stack;

	return ( *this );

}

RPN::~RPN( void ) {
}

// Exceptions
RPN::invalidArgument::invalidArgument( const std::string& msg ) : std::runtime_error( msg ) {
}

RPN::emptyStack::emptyStack( const std::string& msg ) : std::runtime_error( msg ) {
}

RPN::divisionByZero::divisionByZero( const std::string& msg ) : std::runtime_error( msg ) {
}


// Getters
double RPN::getResult( void ) const {

	if ( _stack.empty() )
		throw RPN::emptyStack( "Empty stack" );
	else if ( _stack.size() > 1 )
		throw RPN::invalidArgument( "Invalid argument" );

	return ( _stack.top() );

}

// Private methods
void RPN::_executeStack( double ( RPN::*f )( double, double ) ) {

	double a;
	double b;

	if ( _stack.size() < 2 )
		throw RPN::emptyStack( "Empty stack" );

	a = _stack.top();
	_stack.pop();
	b = _stack.top();
	_stack.pop();
	_stack.push( ( this->*f )( a, b ) );

}

double RPN::_plus( double a, double b ) {

	return ( b + a );

}

double RPN::_minus( double a, double b ) {

	return ( b - a );

}

double RPN::_multiply( double a, double b ) {

	return ( b * a );

}

double RPN::_divide( double a, double b ) {

	if ( a == 0 )
		throw RPN::divisionByZero( "Division by zero" );

	return ( b / a );

}