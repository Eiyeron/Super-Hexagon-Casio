#include "pattern.h"
#include "struct.h"
#include "wall.h"

static Pattern* allocatePattern(Pattern* pattern, unsigned int pattern_length) {
	// Freaking free cascade
	pattern->side = (unsigned char*) malloc(sizeof(unsigned char) * pattern_length);
	if(pattern->side == NULL) {
		return NULL;
	}
	pattern->distance = (unsigned short*)malloc(sizeof(unsigned short) * pattern_length);
	if(pattern->distance == NULL) {
		free(pattern->side);
		return NULL;
	}
	pattern->wall_length = (unsigned short*)malloc(sizeof(unsigned short) * pattern_length);
	if(pattern->wall_length == NULL) {
		free(pattern->distance);
		free(pattern->side);
		return NULL;
	}
	return pattern;
}

Pattern* readPattern(Pattern* pattern, unsigned char* data) {
	unsigned int i;
	pattern->length = data[0];
	pattern->cooldown = data[1];
	allocatePattern(pattern, pattern->length);
	if(pattern  == NULL) return NULL;

	for(i = 0; i < data[0]; i++) {
		unsigned int offset = i*5 + 2;
		pattern->side[i] = data[offset];
		pattern->distance[i] = (data[offset + 1]<<8) + data[offset + 2];
		pattern->wall_length[i] = (data[offset + 3]<<8) + data[offset + 4];
	}
	return pattern;
}

void addPattern(Game_Data* data, Pattern* pattern, unsigned char offset) {
	unsigned int i;
	for(i = 0; i < pattern->length; i++) {
		// Build wall
		data->list = addWall(data->list, pattern->distance[i] + pattern->wall_length[i] + 128, pattern->wall_length[i], 1, (pattern->side[i] + offset)%data->nb_lines);
	}
}

Pattern* freePattern(Pattern* pattern) {
	free(pattern->side);
	free(pattern->distance);
	free(pattern->wall_length);
	return NULL;
}