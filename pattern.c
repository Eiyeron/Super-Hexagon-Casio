#include "pattern.h"
#include "struct.h"
#include "wall.h"

Pattern* readPattern() {

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