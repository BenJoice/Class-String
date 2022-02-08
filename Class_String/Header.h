#include <iostream>

using namespace std;


int StrLen( char* );
void StrCpy( char*, char* );
bool StrCmp( char*, char* );

class String
{
public:
	String();
	String( const char* _str );

	String( const String& );

	~String();

	String& operator=( const String& );
	String& operator=( const char* s );
	friend String operator+( const String&, const String& );
	String& operator+=( const String& );

	friend bool operator==( const String&, const String& );
	//friend bool operator=(const String&,  char*);
	friend bool operator!=( const String&, const String& );
	friend bool operator>( const String&, const String& );
	friend bool operator>=( const String&, const String& );
	friend bool operator<( const String&, const String& );
	friend bool operator<=( const String&, const String& );

	const char& operator[]( int ) const;
	char& operator[]( int );

	friend std::ostream& operator<<( std::ostream&, const String& );
	friend std::istream& operator>>( std::istream&, String& );
	int lenght();
private:
	char* str;
	int* counter;
	int len;
};




String::String( const char* s ):counter(new int)
{
	//if (*this->counter<1 )
	//{
		*counter = 1;
	//}
	len = strlen( s );
	str = new char[len + 1];//распределение памяти
	StrCpy( str, ( char* )s );// инициализация указателя
}
//конструктор по умолчанию
String::String():counter(new int)
{
	len = 0;
	str = new char[1];
	str[0] = '\0';//строка заданная по умолчанию
	*counter = 1;

}




String::String( const String& rhs )
{
	counter = rhs.counter;
	str = new char[StrLen( rhs.str ) + 1];
	StrCpy( str, rhs.str );
	len = rhs.len;
	++* counter;
}

String::~String()
{
	//delete str;
	if ( *counter > 1 )
	{
		delete[] str;
		//str = nullptr;
	}
	if ( *counter > 0 )
	{
		--* counter;
	}
	if ( *counter == 0 )
	{
		delete[] str;
		//str = nullptr;
		delete[] counter;
		//counter = nullptr;
		std::cout << "my Class String deleted the object. The counter equals 0" << std::endl;
	}
}

// ---

String& String::operator=( const String& rhs )
{
	if ( this != &rhs )
	{
		delete[] this->str;
		this->str = new char[StrLen( rhs.str ) + 1];
		StrCpy( this->str, rhs.str );
		counter = rhs.counter;
		len = rhs.len;
	}

	return *this;
}

String& String::operator=( const char* s )
{
	if ( str != s && (*counter>1) )
	{
		--*counter;
		int* count = new int;
		counter = count;
		*counter = 1;
	}
	delete[] str;
	len = strlen( s );
	str = new char[len + 1];
	StrCpy( str, ( char* )s );
	return *this;
}


String& String::operator+=( const String& rhs )
{
	
	int sz = this->len + rhs.len ;

	char* ts = new char[sz + 1];

	for ( int i = 0; i < StrLen( this->str ); i++ )
		ts[i] = this->str[i];
	for ( int ii = StrLen( this->str ), j = 0; ii <= sz; ii++, j++ )
		ts[ii] = rhs.str[j];

	delete[] this->str;
	this->str = ts;
	this->len += rhs.len;
	return *this;
}
String operator+( const String& lhs, const String& rhs )
{
	String ts = lhs;

	return ts += rhs;
}

// --

bool operator==( const String& lhs, const String& rhs )
{
	return StrCmp( lhs.str, rhs.str );
}


bool operator!=( const String& lhs, const String& rhs )
{
	return !(StrCmp( lhs.str, rhs.str ));
}

bool operator>( const String& lhs, const String& rhs )
{
	return (StrLen( lhs.str ) > StrLen( rhs.str )) ? true : false;
}

bool operator>=( const String& lhs, const String& rhs )
{
	return (StrLen( lhs.str ) >= StrLen( rhs.str )) ? true : false;
}

bool operator<( const String& lhs, const String& rhs )
{
	return (StrLen( lhs.str ) < StrLen( rhs.str )) ? true : false;
}

bool operator<=( const String& lhs, const String& rhs )
{
	return StrLen( lhs.str ) <= StrLen( rhs.str );
}

// ---

const char& String::operator[]( int i ) const
{
	//std::cerr << "Index out of range. \n";
	return (i >= 0 && i < StrLen( this->str )) ? this->str[i] : 0;
}

char& String::operator[]( int i )
{
	static char DUMMY;
	DUMMY = '\0';
	//std::cerr << "Index out of range. \n";
	return (i >= 0 && i < StrLen( this->str )) ? this->str[i] : DUMMY;
}

inline int String::lenght()
{
	return this->len;
}

// ---

std::ostream& operator<<( std::ostream& os, const String& obj )
{
	return os << obj.str;
}

std::istream& operator>>( std::istream& is, String& obj )
{
	char BUFF[2048];

	is.getline( BUFF, sizeof BUFF );
	obj = BUFF;

	return is;
}

// ---

int StrLen( char* _str )
{
	int size = 0;

	for ( ; _str[size] != 0; size++ );

	return size;
}

void StrCpy( char* in_str, char* src_str )
{
	for ( int i = 0; i < StrLen( in_str ); i++ )
		in_str[i] = src_str[i];
}

bool StrCmp( char* str_f, char* str_s )
{
	int i = 0;

	for ( ; str_f[i] == str_s[i] && i < StrLen( str_f ); i++ );

	return i == StrLen( str_f );
}
int main()
{
	//String s = "asdfa"; // O(n)
	//String s2 = s; // O(1)
	//s2="aaaa" ;
	//s2 += "bbbb";
	//s2 = "ll";
	//String s3(s2);
	//s = s + s3;
	////String s2 = "aaaaaaaa";
	//if (s[0]==s[s.lenght()] )
	//{
	//	cout << "yes\n";
	//}
	//for (int i=0;i<s.lenght();i++ )
	//{
	//	s[i] = '!';
	//}
	//cout << endl;
	//cout << s;
	//

	//String s1( s );
	//String a;
	//cin >> a;
	//if (a.lenght()<=s1.lenght() )
	//{
	//	cout << "\na<=s1\n";
	//}
	//if (a<s1 )
	//{
	//	cout << "\na<s1";
	//}
	//else
	//{
	//	cout << "\na!< s1";
	//}
	//cout << endl;

	//
	String s1;
	cin >> s1;
	String s2( s1 );
	String s3 = s2;
	cout << s2[0];
	s2[0] = 'Y';
	
}