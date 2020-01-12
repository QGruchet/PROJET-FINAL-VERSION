#include "famille.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "utils.h"

#define SKIP_IF_ASSIGNED(seq) if(seq.famille != FAMILLE_INCONNUE) continue; //Permet d'alleger le code en le rendant plus lisible, ce if etant repete plusieurs fois

//creer un tableau de type DISTANCE contenant toutes les distances entre les fonctions
void pairwise_distance(SEQUENCE seq_list[], int max_seq, DISTANCE (*distance)(SEQUENCE, SEQUENCE), DISTANCE all_distance[MAXFILES][MAXFILES]) // on remplit que i<j
{
	for(int i = 0; i < max_seq; i++)
	{															//on parcours toutes les sequences
		for(int j = i + 1; j < max_seq; j++)
		{
			all_distance[i][j] = distance(seq_list[i], seq_list[j]);    //on palce dans le tableau toute les sequences
		}
	}
}

//Fonction pour trouver le minimum des distances dans le tableau all_distance
float distance_minimum(SEQUENCE seq_list[], int max_seq, DISTANCE all_distance[MAXFILES][MAXFILES])
{
	
	float min = NO_SEQUENCE; 
	for(int i = 0; i < max_seq; i++)
	{
		SKIP_IF_ASSIGNED(seq_list[i])

		for(int j = i + 1; j < max_seq; j++)
		{
			
			SKIP_IF_ASSIGNED(seq_list[j])

			min = MIN(min, all_distance[i][j].dist);
		}
	}
	return min;
}


int find_max_occurence(SEQUENCE seq_list[], float dmin, int compt, DISTANCE all_distance[MAXFILES][MAXFILES])
{
	int max_per_row = 0;

    // for each row
	for(int i = 0; i < compt; i++)
	{
		SKIP_IF_ASSIGNED(seq_list[i])

		int count = 0;

		// for each column
		for(int j = i+1; j < compt; j++)
		{
			SKIP_IF_ASSIGNED(seq_list[j])

			if(all_distance[i][j].dist == dmin)
			{
				count++;
			}
		}


		max_per_row = MAX(max_per_row, count);
	}

	return max_per_row;
 }


//Permet d'assigner chaque séquence a sa famille
void assign_family(SEQUENCE seq_list[], int compt, float dmin, DISTANCE all_distance[MAXFILES][MAXFILES], int num_family)
{
	int max_occurence = find_max_occurence(seq_list, dmin, compt, all_distance);

	for(int i = 0; i < compt; i++)
	{
		SKIP_IF_ASSIGNED(seq_list[i])
		
		int count = 0;

		// for each column
		for(int j = 0; j < compt; j++)
		{
		
			SKIP_IF_ASSIGNED(seq_list[j])

			if(all_distance[i][j].dist == dmin)
			{
				count++;
				seq_list[j].famille = num_family;
			}
		}

		if(count == max_occurence)
		{
			seq_list[i].famille = num_family;
		}

	}
}

//Affiche les differentes familles grâce à leur numéro unique à chaque famille
void show_family(SEQUENCE seq_list[], char* file_list[], int compt)
{
	for(int i = 0; i < 7; i++)
	{
		printf("\t\tFamille n°%d :\n", i);
		for(int j = 0; j < compt; j++)
		{
			if(seq_list[j].famille == i)
			{
				printf("\t    ");
				show_sequence(seq_list[j]);
			}
			else continue;

		}
		printf("\n");
	}
}
//Cette fonction permet de creer les differents repertoires qui vont contenir les familles d'une même famille
void create_repertory()
{
	//On creer, pour plus de lisibilité, un dossier globale contenant les dossiers des familles 
	if(opendir("Famille") == NULL)
	{
		system("mkdir Famille");
	}

	const int compt = 0;
	//On creer ensuite un dossier pour chaque famille
	switch(compt)
	{
		case(0):
		if(opendir("Famille/famille_0") == NULL)
		{
			system("mkdir Famille/famille_0");
		}
		case(1):
		if(opendir("Famille/famille_1") == NULL)
		{
			system("mkdir Famille/famille_1");
		}
		case(2):
		if(opendir("Famille/famille_2") == NULL)
		{
			system("mkdir Famille/famille_2");
			}
		case(3):
		if(opendir("Famille/famille_3") == NULL)
		{
			system("mkdir Famille/famille_3");
		}
		case(4):
		if(opendir("Famille/famille_4") == NULL)
		{
			system("mkdir Famille/famille_4");
		}
		case(5):
		if(opendir("Famille/famille_5") == NULL)
		{
			system("mkdir Famille/famille_5");
		}
		case(6):
		if(opendir("Famille/famille_6") == NULL)
		{
			system("mkdir Famille/famille_6");
		}
		break;
	}
}


//Permet de regrouper chaque fichier contenant les sequences dans leur repertoire correspondant a leur familles
void regroup_family(SEQUENCE seq_list[], char* file_list[], int compt)
{
	char command[512];
	create_repertory();
	for(int i = 0; i <8; i++)
	{
		for(int j = 0; j < compt; j++)
		{
			if(seq_list[j].famille == i)
			{
				sprintf(command, "cp %s Famille/famille_%d/", file_list[j], i);
				system(command);
			}
		}
	}
}