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
			_executeOperation( &RPN::_add );
		else if (token == "-")
			_executeOperation( &RPN::_subtract );
		else if (token == "*")
			_executeOperation( &RPN::_multiply );
		else if (token == "/")
			_executeOperation( &RPN::_divide );
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
int RPN::getResult( void ) const {

	if ( _stack.empty() )
		throw RPN::emptyStack( "Error: Empty stack" );
	else if ( _stack.size() > 1 )
		throw RPN::invalidArgument( "Error: Invalid argument" );

	return ( _stack.top() );

}

// Private methods
void RPN::_executeOperation( int ( RPN::*f )( int, int ) ) {

	int a;
	int b;

	if ( _stack.size() < 2 )
		throw RPN::emptyStack( "Error: Empty stack" );

	a = _stack.top();
	_stack.pop();
	b = _stack.top();
	_stack.pop();
	_stack.push( ( this->*f )( a, b ) );

}

int RPN::_add( int a, int b ) {

	return ( b + a );

}

int RPN::_subtract( int a, int b ) {

	return ( b - a );

}

int RPN::_multiply( int a, int b ) {

	return ( b * a );

}

int RPN::_divide( int a, int b ) {

	if ( a == 0 )
		throw RPN::divisionByZero( "Error: Division by zero" );

	return ( b / a );

}