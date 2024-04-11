/* BY: Jumps Are Op. (jumpsareop@gmail.com)
 * LICENSE: GPLv3-or-later
 */

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include "shyard.h"
#include "stack.h"

#define LEN(x) (sizeof(x)/sizeof(*(x)))

static const char opnames[] = {
	[BRUH] = '(',
	[ADD] = '+',
	[SUB] = '-',
	[MUL] = '*',
	[DIV] = '/'
};

static const unsigned opprio[] = {
	[ADD] = 1,
	[SUB] = 1,
	[MUL] = 2,
	[DIV] = 2
};

static void parse(char*);

int main(){
	char *line = NULL;
	size_t n = 0;

	initstack();
	while(getline(&line, &n, stdin) != -1)
		parse(line);
	if(ferror(stdin)){
		perror("stdin");
		return 1;
	}
}

static void parse(char *line){
	const char *delims = " \t\n";
	char *token = strtok(line, delims);
	char c = 1;
	enum Op i;
	bool digit = true, bracket = false;

	while(token){
		for(; (c = *token); token++){
			if(isdigit(c)){
				if(!digit){
					putchar(' ');
					digit = true;
				}
				putchar(c);
				goto end;
			}
			if(c == '('){
				push(BRUH);
				goto end;
			}
			if(c == ')'){
				while(!isempty() && ctop() != BRUH){
					putchar(opnames[pop()]);
					digit = true;
					bracket = true;
				}
				if(ctop() == BRUH){
					pop();
				}else{
					fputs("You're too lazy to balance\n",
					      stderr);
					exit(1);
				}
				goto end;
			}
			if(c == '_')
				continue;
			for(i = 0; i < LEN(opnames); i++){
				if(c == opnames[i]){
					if(bracket)
						bracket = false;
					else
						digit = false;

					while(!isempty() &&
					      opprio[ctop()] >= opprio[i]){
						putchar(opnames[pop()]);
						digit = true;
					}
					push(i);
					goto end;
				}
			}
			assert(0);
			end:
		}
		token = strtok(NULL, delims);
	}
	while(!isempty()){
		if(ctop() == BRUH){
			fputs("You're too lazy to balance\n",
			      stderr);
			exit(1);
		}
		putchar(opnames[pop()]);
	}
	putchar('\n');
}
