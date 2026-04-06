#ifndef TOKEN_TYPE
#define TOKEN_TYPE

typedef enum {
	INC_MEM_PTR,
	DEC_MEM_PTR,
	INC_BLK_VAL,
	DEC_BLK_VAL,
	CUR_BLK_OPEN,
	CUR_BLK_CLOSE,
	GET_CHAR,
	PUT_CHAR
} TokenType;

typedef struct {
	TokenType 	type;
	int 		value;
	int 		jump; 
} Token;

#endif
