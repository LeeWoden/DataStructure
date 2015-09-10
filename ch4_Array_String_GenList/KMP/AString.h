#ifndef KMP_H
#define KMP_H

#include <iostream>
using namespace std;

const int defaultSize = 256;

class AString
{
public:
	AString(int sz = defaultSize);
	AString(const char *str);
	AString(const AString &str);
	~AString() { delete []ch; }
	AString & operator = ( const AString &str );
	AString operator + ( const AString &str );
	AString operator () ( int pos, int length );

	AString substr(int pos, int length);
	void getNext(int *next);
	int KMP(AString &str, int k, int *next) const;
	AString & replace(AString &t, AString &v);

	int Length() const { return curLength; }

private:
	char *ch;
	int maxSize;
	int curLength;

	friend istream & operator >> ( istream &in, AString &str )
	{
		in >> str.ch;
		str.curLength = strlen(str.ch);
		return in;
	}

	friend ostream & operator << ( ostream &out, AString &str )
	{
		out << str.ch;
		return out;
	}
};

#endif