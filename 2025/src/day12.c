#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data/list.h"

typedef struct {
	int occupied [3][3];
	size_t num_occupied;
} piece;

piece pieces[6];

static list * get_input(char * filename) {
	FILE * fp = fopen(filename, "r");
	list * ret = create_list();
	size_t last_line_len = 8;
	char * line = calloc(last_line_len, sizeof(char));
	int chars_read;
	for (size_t i = 0; i < 6; i++) {
		getline(&line, &last_line_len, fp);
		pieces[i].num_occupied = 0;
		for (size_t row = 0; row < 3; row++) {
			getline(&line, &last_line_len, fp);
			for (size_t col = 0; col < 3; col++) {
				if (line[col] == '#') {
					pieces[i].occupied[row][col] = 1;
					pieces[i].num_occupied++;
				} else {
					pieces[i].occupied[row][col] = 0;
				}
			}
		}
		getline(&line, &last_line_len, fp);
	}
	while ((chars_read = getline(&line, &last_line_len, fp)) != -1) {
		if (!strcmp(line, "\n")){
			break;
		}
		list_push(ret, line);
		line = calloc(last_line_len, sizeof(char));
	}
	free(line);
	return ret;
}
void day12part1(char* filename){
	size_t res = 0;
	list * input = get_input(filename);
	char * line, * tok;
	size_t i;
	size_t x, y, required_space, available_space, n_required;
	LIST_FOR_EACH(line, input) {
		required_space = 0;
		tok = strtok(line, " ");
		sscanf(tok, "%lux%lu", &x, &y);
		for (i = 0; i < 6; i++) {
			tok = strtok(NULL, " ");
			n_required = atol(tok);
			required_space += pieces[i].num_occupied * n_required;
		}
		available_space = x * y;
		printf("%lu/%lu\n", required_space, available_space);
		if (required_space <= available_space) {
			res++;
		}
	}
	list_free(input);
	printf("result: %ld\n", res);
}
void day12part2(char* filename){
	(void) filename;
}
