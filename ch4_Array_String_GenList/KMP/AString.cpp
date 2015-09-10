#include "AString.h"
#include <cassert>
#include <cstring>
using namespace std;

AString::AString(int sz) : maxSize( sz ), curLength( 0 )
{
	ch = new char[ maxSize + 1 ]; //串结束符'\0'占一个空间
	assert( ch );
	ch[0] = '\0';
}

AString::AString(const char *str)
{
	int len = strlen( str );
	maxSize = (len > defaultSize) ? len : defaultSize;
	curLength = len;

	this->ch = new char[ maxSize + 1 ];
	assert( ch );

	strcpy(ch, str);
}

AString::AString(const AString &str)
{
	maxSize = str.maxSize;
	curLength = str.Length();

	ch = new char[ maxSize + 1 ];
	assert( ch );

	strcpy( ch, str.ch );
}

AString AString::substr(int pos, int length)
{
	AString temp( maxSize );
	if ( pos < 0 || length < 0 )
		return temp;
	length = ( pos + length - 1 < maxSize ) ? length : maxSize - pos;
	for ( int i = 0; i < length; i++ )
	{
		temp.ch[ i ] = ch[ pos + i ];
	}
	temp.ch[ length ] = '\0';
	return temp;
}

AString AString::operator () ( int pos, int length )
{
	return substr(pos, length);
}

AString & AString::operator = ( const AString &str )
{
	if ( this == &str )
		return *this;

	delete []ch;
	maxSize = str.maxSize;
	curLength = str.curLength;
	ch = new char[ maxSize + 1 ];
	assert( ch );
	strcpy( ch, str.ch );

	return *this;
}

AString AString::operator + ( const AString &str )
{
	int tmpLength = this->curLength + str.curLength;
	int tmpMax = ( maxSize > tmpLength ) ? maxSize : tmpLength;
	AString tmp( tmpMax );

	tmp.curLength = tmpLength;
	strcpy( tmp.ch, this->ch );
	strcat( tmp.ch, str.ch );
	return tmp;
}

void AString::getNext(int *next) 
{
	next[0] = -1;
	int i = 1, k = -1;
	while ( i < this->curLength )
	{
		if ( k == -1 )
			next[i++] = ++k;
		else if ( ch[k] == ch[i] )
			next[i++] = ++k;
		else
			k = next[k];
	}
}

int AString::KMP(AString &pat, int k, int *next) const
{
	int i = k, j = 0;
	while ( i < curLength && j < pat.Length() )
	{
		if ( j == -1 || ch[i] == pat.ch[j])
			i++, j++;
		else
			j = next[j];
	}
	
	if ( j == pat.Length() )
		return i - j;
	else
		return -1;
}

AString & AString::replace(AString &t, AString &v)
{
	int *next = new int[ t.Length() ];
	t.getNext( next );

	int i = 0;
	AString tmp;
	while ( i <= curLength - t.Length() )
	{
		int pos = KMP(t, i, next);
		if ( pos == -1 )
			break;
		tmp = tmp + this->substr(i, pos - i) +v;
		i = pos + t.Length();
	}
	tmp = tmp + this->substr(i, curLength - i);
	*this = tmp;
	delete []next;
	return *this;
}