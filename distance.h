#include "sequence.h"

typedef struct 
{
	float dist;

}DISTANCE;

DISTANCE distance_Hamming(SEQUENCE seq1, SEQUENCE seq2);
DISTANCE distance_recursive(SEQUENCE seq1, SEQUENCE seq2);
void find_pairs(
	const SEQUENCE seq_list[], 
	int max_seq, 
	char* file_list[],
	DISTANCE (*distance)(SEQUENCE, SEQUENCE));