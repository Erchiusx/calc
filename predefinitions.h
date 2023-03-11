#include <string.h>
#include <stdbool.h>
FILE* fin = stdin;
typedef enum{
	operator, int_num, float_num, separator, query
} tokenType;

typedef struct{
	tokenType type;
	int operand, floatpower;
} Token;

typedef struct{
	bool succeed;
	Token result;
	enum{} errType;
	int errIndex;
} Message;

int read( Token *token );
Message eval( Token *token, int num );
void print( Message message, Token *token, int num );