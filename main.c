#include "predefinitions.h"
#include "read.h"
#include "eval.h"
#include "print.h"

void base_help(){
	printf("calculator v0.0.1 powered by Erchius.\n");	
}

int help(){
	base_help();
	printf("usage:\n");
	printf("calculator | calculator -i	run interactively.\n");
	printf("calculator -h				print usage information.\n");
	printf("calculator -c \"<expression>\"	calculate the input expression, then output.\n");
	printf("calculator -f \"<file name>\"	read from the file, then calculate and output.\n");
	return 0;
}

int help( char command ){
	switch( command ){
	case 'c':
		base_help();
		printf("calculator -c \"<expression>\"	calculate the input expression, then output.\n");
		break;
	case 'f':
		base_help();
		printf("calculator -f \"<file name>\"	read from the file, then calculate and output.\n");
		break;
	default:
		printf( "Unknown option: -%c, try `calculator -h`.\n", command );
		help();
		break;		
	}
	return 0;
}

int help( char *str, char* command ){
	printf( str, command );
	return 0;
}

void compute(){
	Token token[100] = {0};
	int num_token = read( token );
	if( ~num_token )
		print( eval( token, num_token ), token, num_token );
	else if( num_token ){
		printf("error occurred during I/O\n");
		exit(1);
	}
	else{
		return;
	}
	if( feof(fin) )
		exit(0);
}

int main(int argc, char const *argv[])
{
	switch( argc ){
	case 1:
		while(1)
			compute();
		break;
	case 2:
		if( argv[1][0] != '-' )
			return help( "Not understood: %s, try `calculator -h`.", argv[1] );
		if( strlen( argv[1] ) != 2 )
			return help( "Unknown option: %s, try `calculator -h`.", argv[1] );
		switch( argv[1][1] ){
		case 'h':
			return help();
		default :
			return help( argv[1][1] );
		}
	}
	return 0;
}