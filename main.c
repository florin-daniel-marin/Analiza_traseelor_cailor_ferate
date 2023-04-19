#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functii_graf.h"
#include "queue.h"
#include "Dijkstra_Kruskal.h"

char *read_text_file(FILE *f, char *buffer)
{
    int i = 0;
    char line_text[50];

    if(fgets(line_text, 50, f) == NULL)
    {
        strcpy (buffer, "\0");
        return buffer;
    }

    strcat (buffer, line_text);
    while ((buffer[strlen(buffer)-i] == '\n') || (buffer[strlen(buffer)-i] == '\r') || (buffer[strlen(buffer)-i] == '\0'))
        i++;
    buffer[strlen(buffer)-i+1]= '\0';

    return buffer;
}



int main()
{
    FILE *f, *g;
    int i = 0, SIZE_CHUNK = 100, SIZE_MULTI = 1; 

    //din _all_files.txt se iau rutele de tren si se pun in path_ruta_tren:
    char path_ruta_tren[50];

    //text file cu numele "path_ruta_tren" se citeste rand cu rand -> rand_din_ruta_tren
    //apoi se pune numele statiei in "statie", iar distanta in "distanta_intre_statii"
    char rand_din_ruta_tren[50];
    char ruta[50];
    char statie[50];
    char *token;
    int distanta_intre_statii; 

    i = 0;
    queue_t *queue = queue_create(SIZE_CHUNK);

    if ((f = fopen("input/_all_files.txt","rt")) == NULL)
    {
        printf("1Nu s-a putut deschide!\n");
        exit(1);
    }

    while (1)
    {
        //din "_all_files.txt citesc" fiecare rand si il pun in "path_ruta_tren"
        strcpy(path_ruta_tren, "input/\0");

        strcpy(ruta, "\0");
        strcpy(ruta, read_text_file(f, ruta));

        if(!strcmp(strcat(path_ruta_tren, ruta), "input/\0"))
            break;

        strcpy(ruta, strtok(ruta, ".txt"));
        token = strtok(NULL, "\0");
        token = strtok(NULL, "\0");

        if ((g = fopen(path_ruta_tren, "rt")) == NULL) //deschid in g <- ruta.txt
        {
            printf("2Nu s-a putut deschide!\n");
            exit(1);
        }

        while (1)
        {
            //se citeste text file-ul "path_ruta_tren".txt rand cu rand
            strcpy(rand_din_ruta_tren, "\0");

            if(!strcmp(strcpy(rand_din_ruta_tren, read_text_file(g, rand_din_ruta_tren)), "\0"))
                break;

            //se pune numele statiei in "statie", iar distanta in "distanta_intre_statii" 
            strcpy(statie, strtok(rand_din_ruta_tren, ","));
            distanta_intre_statii = strtol(strtok(NULL, ","), NULL, 10);

            //la fiecare al SIZE_CHUNK * SIZE_MULTI rand din text file, se realoca alte SIZE*CHUNK memorie pentru alte SIZE*CHUNK noduri in coada
            //SIZE_CHUNK = 100, SIZE_MULTI = 1..., la fiecare 100 de noduri in coada, se mai aloca inca 100.
            if (i == SIZE_MULTI * SIZE_CHUNK)
                {
                    SIZE_MULTI ++;
                    queue = realloc (queue, SIZE_MULTI*SIZE_CHUNK* sizeof(queue_t));
                }

            //nodul format din statie si distanta se introduce in coada:
            queue_push(queue, statie, distanta_intre_statii, ruta); 

            //i-ul calculeaza cate randuri/noduri sunt in text files/coada:
            i++;
        }
        fclose(g);
    }
    fclose (f);

    //creez 4 structuri de tip graf, construiesc graf-urile prin matricea de adiacenta, apoi le afisez in text files
    graf *graf_neorientat, *graf_orientat, *graf_neorientat_cost, *graf_orientat_cost;
    
    graf_neorientat = graf_create(queue->index_max);
    graf_orientat = graf_create(queue->index_max);
    graf_neorientat_cost = graf_create(queue->index_max);
    graf_orientat_cost = graf_create(queue->index_max);

    graf_matrix_create(queue, graf_neorientat, "ns");
    graf_matrix_create(queue, graf_neorientat_cost, "nc");
    graf_matrix_create(queue, graf_orientat, "os");
    graf_matrix_create(queue, graf_orientat_cost, "oc");

    //mst al grafului graf_neorientat_cost
    graf *min_span_tree;
    min_span_tree = graf_create (queue->index_max);
    kruskalMST (graf_orientat_cost, min_span_tree, "output/1.txt", "output/mst_lungime_total.txt");

    graf_display (min_span_tree, "output/mst_graf_neorientat_cost.txt");
    graf_display (graf_neorientat, "output/Graf_neorientat.txt");
    graf_display (graf_neorientat_cost, "output/Graf_neorientat_cost.txt");
    graf_display (graf_orientat, "output/Graf_orientat.txt");
    graf_display (graf_orientat_cost, "output/Graf_orientat_cost.txt");
    
    //in nr_noduri.txt se afla numarul de noduri pentru cele 2 tipuri de grafuri
    if ((f = fopen("output/nr_noduri.txt", "wt")) == NULL)
    	exit(1);
    	
    fprintf (f, "Numarul de noduri in ortientat: %d\n", graf_orientat->varf);
    fprintf (f, "Numarul de noduri in neorientat: %d", graf_neorientat->varf);
    fclose(f);

    //in nr_muchii.txt se afla numarul de muchii pentru cele 2 tipuri de grafuri  
    if ((f = fopen("output/nr_muchii.txt", "wt")) == NULL)
    	exit(1);

    graf_neorientat_edges(graf_neorientat);
    graf_orientat_edges (graf_orientat);

    fprintf (f, "Numarul de muchii in graf neorientat: %d\n", graf_neorientat->muchii);
    fprintf (f, "Numarul de muchii in graf orientat: %d", graf_orientat->muchii);
    fclose(f);
    //-----------------------------------------03-------------------------------------------------
    //-----------Găsiți stațiile consecutive care au distanța minimă/maximă între ele.------------
    //----(rezultatele în fișierele /dist_min_doua_statii.txt și /dist_max_doua_statii.txt)-------
    //--------------------------------------------------------------------------------------------
    graf_display_val (queue, graf_orientat_cost, graf_min_matrix (graf_orientat_cost), "output/dist_MIN_doua_statii.txt");
    graf_display_val (queue, min_span_tree, graf_min_matrix (min_span_tree), "output/mst_dist_MIN_doua_statii.txt");
    graf_display_val (queue, graf_orientat_cost, graf_max_matrix (graf_orientat_cost), "output/dist_MAX_doua_statii.txt");
    graf_display_val (queue, min_span_tree, graf_max_matrix (min_span_tree), "output/mst_dist_MAX_doua_statii.txt");
    //-----------------------------------------04-------------------------------------------------
    //----------------Câți km de cale ferată există în baza noastră de date?----------------------
    //---------------------(rezultatele în fișierul lungime_total.txt)----------------------------
    //--------------------------------------------------------------------------------------------
    graf_all_costs (graf_neorientat_cost, "output/lungime_total.txt");
    
    //----------folosind algoritmul Dijkstra putem rezolva multiple probleme de cost--------------
    //--------------------------------------------------------------------------------------------
    //--Alogirtmul calculeaza drumul de cost minim dintre un nod sursa si toate celelalte noduri--
    //--In cazul problemei, costul reprezinta lungimea, o marime reala. Ruland o data algoritmul,-
    //--Statia cea mai departata de sursa este statia la care distanta este maxima. Rezultatul----
    //--a fost gasit printr-un algoritm ce cauta costul minim si e valabil doar pentru cazul de---
    //--fata.-------------------------------------------------------------------------------------
    //-----------------------------------------05-------------------------------------------------
    //-------------------Calculați drumul de cost minim de la X la orașul Y.----------------------
    //---------------------(rezultatele în fișierul drum_cost_minim.txt)--------------------------
    //--------------------------------------------------------------------------------------------
    //
    char sursa[25];
    char dest[25];
    char tip_graf;
    
    printf("--------------------------------------------------------------------------------------\n");
    printf("-----------Calculati drumul de cost minim de la statia X la statia Y------------------\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("                         ex: Sibiu\n");
    printf("Alegeti orasul sursa: ");
    scanf ("%[^\n]", sursa);
    getchar();
    printf("\n");
    printf("Alegeti orasul destinatie: ");
    scanf ("%[^\n]", dest);
    getchar();
    printf("--------------------------------------------------------------------------------------\n");
    printf("Alegeti tipul de graf pentru reteaua de cai ferate:\nGraf Neorientat: Press: G\nMinimum Span Tree: Press: M\n");
    scanf ("%c", &tip_graf);
    printf("--------------------------------------Output---------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("Graful neorientat reprezinta toate rutele de tren din tara-------------------------------\n");
    printf("Aplicand Dijkstra: rezultatul este ruta cea mai scurta intre 2 statii--------------------\n");
    printf("Mimimum Span Tree reprezinta scheletul retelei cailor ferate-----------------------------\n");
    printf("(intre oricare 2 statii exista un singur drum)-------------------------------------------\n");
    printf("Aplicand Dijkstra, nu exista mai mult de o muchie intre 2 statii, alg nu se aplica pe mst\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("------In drum_cost_minim.txt gasiti drumul de cost minim intre aceste doua orase---------\n");
    printf("----------In departe.txt gasiti cea mai indepartata statie de statia sursa---------------\n");
    printf("----------------In ruta_max.txt gasiti cel mai lung drum (de cost minim)-----------------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("+-+-+-+--Despre graf-uri:-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
    printf("-----graf_neorientat.txt-----------------------------graf_neorientat_cost.txt------------\n");
    printf("-----graf_orientat.txt-------------------------------graf_orientat_cost.txt--------------\n");
    printf("-----mst_graf_neorientat.txt-------------------------<-Minimum Span Tree-----------------\n");
    printf("-----nr_muchii.txt si nr_noduri.txt------------------<-Detalii despre Grafuri------------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("+-+-+-+--Reteaua de cale ferata din Romania:-+-+-+-+--+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-\n");
    printf("-----lungime_total.txt-------------------------------<-Totalul de km de cale ferata------\n");
    printf("-----dist_min_doua_statii.txt------------<-Statiile cu distanta cea mai mica si linia----\n");
    printf("-----dist_max_doua_statii.txt------------<-Statiile cele mai departate si linia----------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("-------------------------------------Sfarsit---------------------------------------------\n");
    printf("-----------------------------------------------------------------------------------------\n");

    
    //--------------------------Operatii pe grafuri----------------------------------------------------------------------------------------------------------
    if ((tip_graf == 'G') || (tip_graf == 'M')){
        // algoritmul dijkstra:
        int a = 9999; 
        int b = 9999;

        if (tip_graf == 'G')
            dijkstra(queue, graf_neorientat_cost, queue_get_index(queue, sursa), 1, "output/distante.txt", &a, &b);
            else dijkstra(queue, min_span_tree, queue_get_index(queue, sursa), 1, "output/distante.txt", &a, &b);
        // apelez algoritmul o singura data, 

        int distanta; // distanta local
        int distanta_max_lcl = 0; // distanta maxim local
        int distanta_max_gen = 0; // distanta maxim general
        int sursa_lcl, sursa_gen; // INDEX pentru sursa local, sursa general
        int dest_lcl, dest_gen; // INDEX pentru destinatie local, destinatie general
        char get_row_from[5000]; // folosit pentru citirea "distante.txt" rand cu rand
        //char ruta_index_noduri[5000], ruta_max_index_noduri[5000]; // string de INDEX-ul statiilor
        char ruta_string_noduri[5000], ruta_max_string_noduri[5000]; // ruta_max_index_noduri convertit in strings

        //deschid 2 fisiere, distante.txt rezultat in urma apelarii dijkstra in nodul sursa: X
        //in ruta.txt voi pune cel mai scurt drum de la X la Y
        if ((f = fopen("output/distante.txt", "rt")) == NULL){
            printf("1Nu s-a putut deschide!\n");
            exit(1);
        }
        if ((g = fopen("output/drum_cost_minim.txt", "wt")) == NULL){
            printf("1Nu s-a putut deschide!\n");
            exit(1);
        }

        while (1){
            //se citeste text file-ul rand cu rand
            strcpy (get_row_from, "\0");
            if ( fgets(get_row_from, 5000, f) == NULL)
                break;
            //randul scos din text este impartit in 4: sursa (INDEX), destinatie(INDEX), distanta in km, intreaga linie in INDEX
            sursa_lcl = strtol( strtok ( get_row_from, ">"), NULL, 10);
            dest_lcl = strtol( strtok ( NULL, "-"), NULL, 10);
            distanta = strtol( strtok ( NULL, "-"), NULL, 10);
            strcpy (ruta_string_noduri, strtok ( NULL, "\n"));
            //ruta.txt voi pune cel mai scurt drum de la x la y
            if (dest_lcl == queue_get_index(queue, dest))
            fprintf (g, "Drumul de cost minim de la %s la %s este: %d km\n", sursa, dest, distanta);
            //caut distanta maxima de la sursa din fisier 
            if (distanta > distanta_max_gen){
                distanta_max_gen = distanta;
                strcpy(ruta_max_string_noduri, ruta_string_noduri);
                dest_gen = dest_lcl;
            }
        }
        fclose(f);
        fclose(g);
        //-----------------------------------------06-------------------------------------------------
        //-------------------Găsiți stația (nodul) cea mai departe de X și drumul.--------------------
        //-------------------------(rezultatele în fișierul departe.txt)------------------------------
        //--------------------------------------------------------------------------------------------
        if ((f = fopen("output/departe.txt", "wt")) == NULL){
            printf("1Nu s-a putut deschide!\n");
            exit(1);
        }
        //PRINT STATII PENTRU RUTA MAXIMA:
        fprintf (f, "Statia cea mai departe de %s este: %s, la distanta de %d km, pe linia:\n", sursa, queue_get_string(queue, dest_gen), distanta_max_gen);
        //while (1){
        fprintf (f, "%s\n", ruta_max_string_noduri);
            //ruta_max_string_noduri = strtok(NULL, " ");
        // if (ruta_max_string_noduri == NULL)
            //    break;
    // }
        fclose (f);
        //-----------------------------------------07-------------------------------------------------
        //-------------------Găsiți toate drumurile de la București la Oradea.------------------------
        //---------------------(rezultatele în fișierul bucuresti_oradea.txt)-------------------------
        //--------------------------------------------------------------------------------------------
        //--Avand in vedere ca nu exista nicio restrictie in ceea ce priveste alegerea drumului,------
        //--Cum ar fi, toate drumurile care duc de la Bucuresti la Oradea, fara sa schimbi trenul sau-
        //--Sa poti sa schimbi trenul numai la statia finala, complexitatea algoritmului de mai jos---
        //--Este V^V.---------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------
        //--Nu e indicat sa il rulati:----------------------------------------------------------------
        //graf_path_two_nodes (graf_neorientat_cost, 0,  queue_get_index(queue, "Oradea"), "bucuresti_oradea.txt");
        //--------------------------------------------------------------------------------------------
        //-----------------------------------------08-------------------------------------------------
        //--Găsiți cele două stații din graf care sunt la distanța maximă (pe drumul de cost minim).--
        //------------------------(rezultatele în fișierul ruta_max.txt)-----------------------------
        //-------------------(Rezultatul ar trebui sa fie Carei -> Tulcea Oras)-----------------------
        //--------------------------------------------------------------------------------------------   
        // apelez dijkstra de n ori, adica cel mai lung drum fara sa treaca de doua ori prin aceasi muchie
        // din toate nodurile grafului, si in acelasi timp caut pe cea mai lunga dupa lungimea distantei in km
        distanta_max_lcl = -9999; 
        distanta_max_gen = -9999;
        for (i = 0; i < min_span_tree->varf; i++){
            if (tip_graf == 'G')
                dijkstra(queue, graf_neorientat_cost, i, 0, "distante.txt", &distanta_max_lcl, &dest_lcl);
                else dijkstra(queue, min_span_tree, i, 0, "distante.txt", &distanta_max_lcl, &dest_lcl);
            if (distanta_max_lcl > distanta_max_gen){
                    distanta_max_gen = distanta_max_lcl;
                    dest_gen = dest_lcl;
                    sursa_gen = i;
            }
        }
        //display ruta maxima
        if ((f = fopen("output/ruta_max.txt", "wt")) == NULL){
            printf("1Nu s-a putut deschide!\n");
            exit(1);
        }
        fprintf(f, "%s -> %s, distanta de: %d km", queue_get_string(queue, sursa_gen), queue_get_string(queue, dest_gen), distanta_max_gen);
        fclose(f);
    } else
    printf ("Te rog sa alegi intre graf neorientat si minimum span tree\n");
    return 0;
}