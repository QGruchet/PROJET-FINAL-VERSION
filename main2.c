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
    char* file_list[MAXFILES];      //file_list contient les noms des fichiers 
    char* directory = name_filedir();
    const int compt = scan_dir(directory, file_list, MAXFILES);  //compt est le nombre de sequence dans le dossier (calculer avec scan_dir)
    
    //on fait une boucle pour stocker les sequence dans seq_list.
    SEQUENCE seq_list[compt];
    for(int j = 0; j < compt; j++)
    {
        seq_list[j] = read_seq(file_list[j]); //Pour chaque fichier, on creer une sequence correspondante
    }

    DISTANCE all_distance[MAXFILES][MAXFILES];
    pairwise_distance(seq_list, compt, &distance_Hamming, all_distance);
    int num_family = 0;

    //on implemente un nouveau numero de famille a chaque tour de boucle
    for(num_family; num_family < compt; num_family++)
    {
       float dmin = distance_minimum(seq_list, compt, all_distance);   //on recalcule le minimum a chaque tour 
       if(dmin == NO_SEQUENCE)
       {        
            break;    //on arrete le for
       }
       //int max_occurence = find_max_occurence(seq_list, dmin, compt, all_distance); 
       assign_family(seq_list, compt, dmin, all_distance, num_family);
       //printf("\n");
    }
    show_family(seq_list, file_list, compt);
    regroup_family(seq_list, file_list, compt);


    //Cette boucle permet de liberer toute la memoire prise au cour de cette partie2
    for(int j = 0; j < compt; j++){
        free(file_list[j]);
        free_sequence(seq_list[j]);
    }
    free(directory);
   
    exit(0);
}