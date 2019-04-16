#include <stdio.h>
#include "9cc.h"

int main(int argc, char **argv){
	if (argc != 2){
		fprintf(stderr, "The number of arguments is incorrect.\n");
		return 1;
	}

	tokenize(argv[1]);
	Node *node = add();

	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	gen(node);

	printf("  pop rax\n");
	printf("  ret\n");
	return 0;
}
