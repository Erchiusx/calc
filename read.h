tokenType getType( char token ){
	switch( token ){
	case ' ':
	case '\t':
		return separator;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return int_num;
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		return operator;
	case '\n':
	case '=':
		return query;
	case '.':
		return float_num;
	default :
		return query;
	}
}

int read( Token *token){
	int x, i=0;
	if( ~( x = fgetc(fin) ) ){
		switch( getType(x) ){
		case separator:
			break;
		case int_num:
			token[0].type = int_num;
			token[0].operand = x;
			break;
		case operator:
			token[0].type = operator;
			token[0].operand = x;
			break;
		case float_num:
			return -1;
		case query:
			return 0;
		}
	}
	tokenType type;
	while( ~( x = fgetc(fin) ) ){
		switch( type = getType(x) ){
		case separator:
			while( type = getType( x = fgetc(fin) ) == separator );
			break;
		case float_num:
			switch( token[i].type ){
			case int_num:
				break;
			case float_num:
				exit(1);
			case operator:
				token[++i].type  = operator;
				token[i].operand = 0;
			}
			token[i].type = float_num;
			token[i].floatpower = 0;
			continue;
		case int_num:
			switch( token[i].type ){
			case float_num:
				token[i].floatpower++;
			case int_num:
				token[i].operand *= 10;
				token[i].operand += x - '0';
				continue;
			case operator:
				token[++i].type = int_num;
			}
			continue;
		case operator:
			token[++i].type 	= operator;
			token[i].operand 	= x;
			continue;
		case query:
			return i;
		}
		switch( type ){
		case float_num:
			token[++i].type 	= float_num;
			token[i].operand 	= 0;
			token[i].floatpower = 0;
			break;
		case int_num:
			token[++i].type 	= int_num;
			token[i].operand 	= x - '0';
			break;
		case operator:
			token[++i].type 	= operator;
			token[i].operand 	= x;
			break;
		case query:
			return i;
		}
	}
}