#include <stdlib.h>
#include <stdio.h>

#ifndef SEQUENCE_H 	//check si on est deja passé par sequenceh
#define SEQUENCE_H
#define MAXFILES 20


#define FAMILLE_INCONNUE -1  //pour chaque famille non assigne on lui attribue un nombre qui est impossible au programme d'atteindre

typedef struct{
  int longueur; //taille de la sequence
  char *nucleotides; //tableau de char 
  int famille; //permet de checker si la seq est affilier a une famille
 }SEQUENCE ;
    
int scan_dir(const char* dir_name, char* file_list[], const int max_files);

SEQUENCE read_seq(char* nom_fichier);
void show_sequence(SEQUENCE seq);
void free_sequence(SEQUENCE seq);

#endif