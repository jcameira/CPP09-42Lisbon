#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>
# include <exception>

class RPN
{
	private:

		std::stack< int > _stack;
		void _executeOperation( int ( RPN::*f )( int, int ) );
		int _add( int a, int b );
		int _subtract( int a, int b );
		int _multiply( int a, int b );
		int _divide( int a, int b );

	public:
    
		//Constructors
		RPN( void );
		RPN( const std::string  &inputStr );
		RPN( const RPN &other );
		RPN &operator=( const RPN &other );
		~RPN( void );

		//Getters
		int getResult( void ) const;


		//Exceptions
		class invalidArgument : public std::runtime_error {

			public:
				explicit invalidArgument( const std::string& msg );

		};

		class emptyStack : public std::runtime_error {

			public:
				explicit emptyStack( const std::string& msg );

		};

		class divisionByZero : public std::runtime_error {

			public:
				explicit divisionByZero( const std::string& msg );

		};	
};

#endif