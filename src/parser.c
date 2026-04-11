
#include "lexer.h"
#include "parser.h"
#include "token.h"
#define MAX 100



/*
 *	Token *lexer(const char *buffer, size_t len, int *main_counter)
 *
 *
 */


void parser(const char *buffer, size_t len){
	assert(len > 0);
	int main_counter = 0;
	Token	*tokens = lexer(buffer, len, &main_counter);
	//Array Of Instructions
	
	Token   *shorted_tokens		= malloc(MAX * sizeof(Token));
	int	 shorted_tokens_ptr	= 0;
	//Shorted Token Store: token type & value : INC_MEM_PTR 10
	
	int 	cur_blk_loc[MAX];
	int 	blk_loc_pos 		= -1;
	int 	tok_size    		=  0;	
	int 	k 			= 0;
	Token	tok[MAX];
	
		for(int i = 0; i < main_counter; i++){
			TokenType T = tokens[i].type;
			
			tok[tok_size].type 	= T; 
			tok[tok_size].value 	= -1;
			tok[tok_size].jump  	= -1;
	tok_size++;	
		
	//---JUMP---	
			tokens[i].jump = -1;
			if(T == CUR_BLK_OPEN){
				cur_blk_loc[++blk_loc_pos] = i;
			}
			if(T == CUR_BLK_CLOSE){
				if(blk_loc_pos < 0){
					fprintf(stderr, "Parser error. \n");
					return;
				}
				int j =	cur_blk_loc[blk_loc_pos];
					tokens[i].jump = j;
			        tokens[j].jump = i;	
				blk_loc_pos--;
			}
	//---
	
	//---COMPRESSION---
		
		
			if( k > 0 && tok_size > 1 
					&& (T == INC_MEM_PTR || T == DEC_MEM_PTR || T == INC_BLK_VAL || T == DEC_BLK_VAL )){
				/*
				 *	When there is 2 tokens in stack 
				 *	they are equal , increase first value by one 
				 *	set pointer back to current pointer minus one 
				 */

				if(tok[tok_size - 2].type == tok[tok_size - 1].type){
					//Same Token In Series Inc The Value 
						
						tok[tok_size - 2].value++;
						tok_size--;
				}

				/*
				 *	when new element is not simmiler to the previous one
				 *	save the old cmd & its value in structured tokens memory 
				 *	replace older one with new one
				 *
				 */
				if( tok_size > 2 && tok[tok_size - 2].type != tok[tok_size - 1].type){
					//store older one into structured tokens memory
					//if memory is not modified yet , value will be equal to 0
					//increase it by one and push it into stack 
					if(tok[tok_size - 2].value == -1){
						tok[tok_size - 2].value++;

					}
					tok[tok_size - 2].value++;
					shorted_tokens[shorted_tokens_ptr].type 	= tok[tok_size - 2].type;
					shorted_tokens[shorted_tokens_ptr].value 	= tok[tok_size - 2].value;
					shorted_tokens[shorted_tokens_ptr].jump		= tok[tok_size - 2].jump;
					
					shorted_tokens_ptr++;
					tok[tok_size - 2].type  = tok[tok_size - 1].type;
					tok[tok_size - 2].value = tok[tok_size - 1].value;
					tok[tok_size - 2].jump  = tok[tok_size - 1].jump;
					tok_size--;			
				}
			}
			
				
			k++;
	//---
		
			
		}
	if(blk_loc_pos > -1){
		fprintf(stderr, "Parser error. \n");	
		return;
	}
	tok_size++;
	free(tokens);
}


