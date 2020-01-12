#include "distance.h"
#include "sequence.h"
#include "string.h"
#include "utils.h"

//Petite fonction pour trouver le minimum de 3 float (utile dans la focntion recursive)
float MIN3(float a, float b, float c)
{
	return MIN(MIN(a, b), c);
}

//Fonction permettant de trouver la distance entre deux nucleotides d'une sequence en suivant le tableau donné
float dist_char(char c1, char c2)
{
	switch(c1)
	{
		case 'A':
			switch(c2) {			
				case 'A': return 0.0;
				case 'C': return 2.0;
				case 'G': return 1.0;
				case 'T': return 2.0;
				default: return 1.5;
			}
		case 'C':
			switch(c2) {			
				case 'A': return 2.0;
				case 'C': return 0.0;
				case 'G': return 2.0;
				case 'T': return 1.0;
				default: return 1.5;
			}
		case 'G':
			switch(c2) {			
				case 'A': return 1.0;
				case 'C': return 2.0;
				case 'G': return 0.0;
				case 'T': return 2.0;
				default: return 1.5;
			}
		case 'T':
			switch(c2) {			
				case 'A': return 2.0;
				case 'C': return 1.0;
				case 'G': return 2.0;
				case 'T': return 0.0;
				default: return 1.5;
			}
		default: return 1.5;
	}

}

//Calcul la distance entre deux sequence et renvoie leur distance dans une structure DISTANCE
DISTANCE distance_Hamming(SEQUENCE seq1, SEQUENCE seq2)
{
	char c1, c2;
	DISTANCE distance;
	distance.dist = 0.0;
	for(int i = 0; i < MAX(seq1.longueur, seq2.longueur); i++)
	{
		c1 = (i >= seq1.longueur ? '-' : seq1.nucleotides[i]);
		c2 = (i >= seq2.longueur ? '-' : seq2.nucleotides[i]);
		distance.dist +=  dist_char(c1,c2);


	}
	return distance;
}


//Fonction permettant egalement de calculer la distance entre deux nucleotide d'une sequence
//Elle ne sera pas utiliser par la suite car l'on s'est rendu compte qu'elle etait tres longue à se terminer
//En effet pour une sequence comme les notres le programme mettait plus d'une demi-heure
//De plus, lors du test, la fonction refait plusieurs fois le meme calcule
//Cette fonction est donc plus qu'inefficace
float calcul_distance_recursive(char* seq1, char* seq2, int depth)
{
	int n = strlen(seq1);			
	int m = strlen(seq2);		//on copie la longueur des deux sequences dont on veux calculer la distance 
	/*printf("%*s %2d %2d: %s %s\n", depth + 1, " ", n, m, seq1, seq2);*/		 //cette ligne sert uniquement a afficher en temps réel ce que fait la fontion
																				//utilise lors d'un test

	if(n == 0)
	{
		return m;
	}
	if(m == 0)					//si l'une des deux sequences est de longueurs nul on renvoie l'autre sequence
	{
		return n;
	}

	char* copie_seq1 = strndup(seq1, n-1);
	char* copie_seq2 = strndup(seq2, m-1);

	const float r1 = calcul_distance_recursive(copie_seq1, seq2, depth + 1) + 1.5;
	const float r2 = calcul_distance_recursive(copie_seq1, copie_seq2, depth + 1) + dist_char(seq1[n - 1], seq2[m - 1]);
	const float r3 = calcul_distance_recursive(seq1, copie_seq2, depth + 1) + 1.5;
    const float result = MIN3(r1, r2, r3);

    free (copie_seq1);			//on libere la memoire alloue
    free (copie_seq2);
    return result;
}

//Cette fonction est celle appelé dans le main
//elle permet à l'aide de la fonction precedente de ranger le resultat dans une structure DISTANCE
DISTANCE distance_recursive(SEQUENCE seq1, SEQUENCE seq2)
{
	DISTANCE distance;
	distance.dist = calcul_distance_recursive(seq1.nucleotides, seq2.nucleotides, 0);
	printf("%f\n", distance.dist);
	return distance;
}

//Cette fonction permet de calculer toutes les distances de chaque fonction sauf qu'une ne soit calcule plus d'une fois
//Elle affiche ensuite le nom des fichier et leurs distances
void find_pairs(
	const SEQUENCE seq_list[], 
	int max_seq, 
	char* file_list[],
	DISTANCE (*distance)(SEQUENCE, SEQUENCE))
{
	
    for(int i = 0; i < max_seq - 1; i++)
    {														//on parcours toutes les sequences sans les parcourir deux fois d'ou le j = i + 1
    	printf("\n");													
        for(int j = i+1; j < max_seq; j++) 
        {
            const DISTANCE dist = distance(seq_list[i], seq_list[j]); 		//la fonction distance permet a tous moments de changer de methode de calcul sans avoir a la changer dans tous les fichiers
            printf("%s, %s, %f\n", file_list[i], file_list[j], dist.dist);
        }
    }
}