#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include "sequence.h"


//permet de scanner le repertoire pour savoir combien de fichier nous avons
//et rempli le tableau file_list contenant les noms des fichiers
int scan_dir(const char* dir_name, char* file_list[],int max_files)
{
    struct dirent* sd;
    DIR *D = opendir(dir_name); //ouvre le dossier 'dir_name'
    int compt = 0;
    if(D == NULL)
    {
        fprintf(stderr, "cannot open %s\n", dir_name);
        return -1;                                      //cas d'erreur d'ouverture de dossier
    }
    fprintf(stderr, "file open : %s\n", dir_name);      // si aucune erreur on affiche le nom du dossier
    while(compt < max_files && (sd = readdir(D)) != NULL)   //on lit les fichier un par un
        {
        if(sd->d_type != DT_REG){               //si c'est bien un fichier on continue la fonction
            continue;
        }
        char* path = (char*) malloc(strlen(dir_name) + 2 + strlen(sd->d_name));
        sprintf(path, "%s/%s", dir_name, sd->d_name);                   //path contient donc l'arborescence du dossier et le nom des fichier
        file_list[compt] = path;            //on met path dans un tableau regroupant tous les noms des fichiers
        compt++;
    }
    closedir(D);
    return compt;
}



SEQUENCE read_seq(char* path) //lire seq
{
    FILE *f;
    char *contenu;
    SEQUENCE seq;
        if ((f = fopen(path, "r")) == NULL)
        {
            printf("Impossible d'ouvrir le fichier %s, il est vide !\n", path); //Si le fichier est vide, on arrete le programme
            free(path);
            exit(0);
        }
        // lis la sequence jusqu'a la fin de la ligne
        fscanf(f, "%m[^\n]", &contenu); // allouer automatiquement de la memoire
        fclose(f);
        seq.longueur = strlen(contenu); //on stocke la longueur de la sequence d'ADN
        seq.nucleotides = contenu; //adopte la chaine
        seq.famille = FAMILLE_INCONNUE;
    return seq;
}
void show_sequence(SEQUENCE seq)
{
	printf("%s\n", seq.nucleotides);  //affiche la sequence
}

void free_sequence(SEQUENCE seq)
{
	free(seq.nucleotides);
	seq.nucleotides = NULL;		//permet de libérer la mémoire
}