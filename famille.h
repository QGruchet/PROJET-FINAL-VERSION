#include "distance.h"
#include "sequence.h"

#define NO_SEQUENCE 2E200 //on defini nos sequences avec une valeur enorme pour etre sûr de jamais l'atteindre

typedef struct 
{
	SEQUENCE* seq;
	int nombre_sequence;
}TAB_SEQ_FREQUENTE;



float distance_minimum(SEQUENCE seq_list[], int max_seq, DISTANCE all_distance[MAXFILES][MAXFILES]);
void research_sequence(SEQUENCE seq_list[], int max_files, char* file_list[], DISTANCE (*distance)(SEQUENCE, SEQUENCE), float distance_min);
void pairwise_distance(SEQUENCE seq_list[], int max_seq, DISTANCE (*distance)(SEQUENCE, SEQUENCE), DISTANCE all_distance[MAXFILES][MAXFILES]);
int find_max_occurence(SEQUENCE seq_list[], float dmin, int compt, DISTANCE all_distance[MAXFILES][MAXFILES]);
void assign_family(SEQUENCE seq_list[], int compt, float dmin, DISTANCE all_distance[MAXFILES][MAXFILES], int num_family);
void show_family(SEQUENCE seq_list[], char* file_list[], int compt);
void create_repertory();
void regroup_family(SEQUENCE seq_list[], char* file_list[], int compt);