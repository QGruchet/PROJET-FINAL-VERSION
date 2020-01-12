#include <stdlib.h>
#include <stdio.h>
#include "sequence.h"
#include "famille.h"
#include <string.h>


//Cette fonction demande à l'utilisateur quel dossier veut-il ouvrir, dans notre cas sequence
char* name_filedir() 
{
	char* file_dir;
	printf("Quel dossier ouvrir ? ");
    scanf("%ms", &file_dir);
	return file_dir;	
}



int main(int argc, char *argv[])
{
	const int max_files = 100;
	char* file_list[max_files];
	char* directory = name_filedir();
	const int compt = scan_dir(directory, file_list, max_files);
	

	SEQUENCE seq_list[compt];
	for(int j = 0; j < compt; j++)
	{
		seq_list[j] = read_seq(file_list[j]);					//Pour chaque fichier, on creer une sequence correspondante
	}
	find_pairs(seq_list, compt, file_list, &distance_Hamming);
	
	


	for(int j = 0; j < compt; j++)
	{
		free(file_list[j]);
		free_sequence(seq_list[j]);
	}
	free(directory);
   
	exit(0);
}