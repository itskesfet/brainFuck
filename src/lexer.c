#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <token.h>

/*
 *	arg: 
 *		*buffer: pointer to array of code 
 *		len:	 size of buffer 
 *		*main_counter return array by Lexer len
 *
 */
Token *lexer(const char *buffer, size_t len, int *main_counter){
	assert(len > 0);	
	Token	*tokens_arr = malloc(len* sizeof(Token));
	int	counter     = 0;
	
	for(int i = 0; i < len; i++){
		char T = buffer[i];

		switch(T)
		{
			case '<': tokens_arr[counter++] = (Token){ DEC_MEM_PTR 		, 1 };
				  break;
			case '>': tokens_arr[counter++] = (Token){ INC_MEM_PTR 		, 1 };
				  break;
			case '+': tokens_arr[counter++] = (Token){ INC_BLK_VAL 		, 1 };
				  break;
			case '-': tokens_arr[counter++] = (Token){ DEC_BLK_VAL 		, 1 };
				  break;
			case '[': tokens_arr[counter++] = (Token){ CUR_BLK_OPEN 	, 1 };
				  break;
			case ']': tokens_arr[counter++] = (Token){ CUR_BLK_CLOSE 	, 1 };
				  break;
			case ',': tokens_arr[counter++] = (Token){ GET_CHAR 	 	, 1 };
				  break;
			case '.': tokens_arr[counter++] = (Token){ PUT_CHAR 	 	, 1 };
				  break;
		}

	}

	*main_counter = counter;
	return tokens_arr;
}
