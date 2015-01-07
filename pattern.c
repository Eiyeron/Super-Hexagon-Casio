#include "pattern.h"
#include "struct.h"
#include "wall.h"

static Pattern* allocatePattern(unsigned int pattern_length) {
	// Freaking free cascade
	pattern->side = malloc(sizeof(unsigned char) * pattern_length);
	if(pattern_length->side == NULL) {
		free(pattern);
		return NULL;
	}
	pattern->distance = malloc(sizeof(unsigned short) * pattern_length);
	if(pattern_length->distance == NULL) {
		free(pattern->side);
		free(pattern);
		return NULL;
	}
	pattern->wall_length = malloc(sizeof(unsigned short) * pattern_length);
	if(pattern_length->wall_length == NULL) {
		free(pattern->distance);
		free(pattern->side);
		free(pattern);
		return NULL;
	}

}

Pattern* readPattern(unsigned char* data, unsigned int length) {
	unsigned char* iterator = data+1;
	unsigned i, pattern_length;
	Pattern* pattern;
	pattern_length = data[0];
	pattern = allocatePattern(pattern_length);
	if(pattern == NULL) return NULL;

	for(int i = 0; i < pattern_length; i++) {
		pattern->side[i] = data[iterator];
		pattern->distance[i] = ((data[iterator]+1)<<8) + (data[iterator]+2);
		pattern->wall_length[i] = ((data[iterator]+2)<<8) + (data[iterator]+3);
		iterator+= 5;
	}

	return pattern;
}

void addPattern(Game_Data* data, Pattern* pattern, unsigned char offset) {
	unsigned int i;
	for(i = 0; i < pattern->length; i++) {
		// Build wall
		addWall(data->list, pattern->distance[i], pattern->wall_length, 1, (pattern->side[i] + offset)%data->nb_lines);
	}
}

Pattern* freePattern(Pattern* pattern) {
	free(pattern->side);
	free(pattern->distance);
	free(pattern->wall_length);
	free(pattern);
	return NULL;
}