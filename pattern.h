#ifndef PATTERN_H
#define PATTERN_H

#include "struct.h"


/**
 * Read a buffer to convert into an dynamically pattern
 * Structure of the pattern data:
 * <pre>
 * XX <=> Pattern length (uint_8)
 * AABBBBCCCC
 * AABBBBCCCC
 * AABBBBCCCC
 * ...
 * </pre>
 * Legend
 * <pre>
 * AA   <=> side (uint_8)
 * BBBB <=> distance(uint_16)
 * CCCC <=> wall_length(uint_16)
 * </pre>
 * @param  data Data to read
 * @return      A brand new pattern
 */
Pattern* readPattern(unsigned char* data, unsigned int length);

/**
 * Add the whole patter to the current game.
 * @param data   data
 * @param offset Offsets the sides to rotate the pattern
 */
void addPattern(Game_Data* data, Pattern* pattern, unsigned char offset);

free* freePattern(Pattern* pattern);

#endif