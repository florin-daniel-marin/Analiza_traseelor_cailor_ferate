# Analiza_traseelor_căilor_ferate
Acest proiect folosește structurile de date: **graph-uri și cozi dublu înlănțuite** și algoritmii specifici graph-urilor: **Dijkstra și Kruskal** pentru analiza traseelor căilor ferate din România (doar traseele C.F.R.).  

Operațiile ce se pot face pe graph-uri includ: măsurarea drumului minim de la o stație la alta, măsurarea celui mai scurt drum/ celui mai lung, determinarea celui mai lung drum din rețea (fără a merge pe un drum între două stații de două ori). 

Proiectul este o temă de la materia **Structuri de Date și Algoritmi**, din anul I, pe care am dezvoltat-o. 
Profesor Cristian Rusu. @cristian-rusu-research
## Teoria Grafurilor
În matematică și informatică, teoria grafurilor studiază proprietățile grafurilor. Un graf este o mulțime de obiecte (numite **noduri**) legate între ele printr-o mulțime de **muchii** cărora le pot fi atribuite direcții (în acest caz, se spune că graful este **orientat**). Un graf poate fi reprezentat geometric ca o mulțime de puncte legate între ele prin linii (de obicei curbe). [^1]

## Dijkstra
Algoritmul lui Dijkstra este o metodă de a stabili drumul de cost minim de la un nod de start la oricare altul dintr-un graf. Numele este dat de Edsger Dijkstra, savantul care l-a descoperit. [^2]

## Kruskal
Algoritmul lui Kruskal este un algoritm în teoria grafurilor care  găsește submulțimea muchiilor care formează un arbore care include toate vârfurile și care este **minimizat** din punct de vedere al costului. Dacă graful nu este conex, atunci algoritmul găsește o pădure parțială de cost minim (un arbore parțial de cost minim pentru fiecare componentă conexă). Algoritmul lui Kruskal este un exemplu de algoritm greedy. [^3]

## Descrierea proiectului
* Rutele de tren se află în directorul **input**
* Rutele sunt citite din fișierele text și sunt introduse într-o structură de tip: **coadă dublu înlănțuită**. Din această coadă se creează apoi graf-urile.
* Graf-urile păstrează informația sub formă de **matrice de adiacență**.
* Toate rezultatele sunt scrise în fișiere .txt în directorul **output**. Elementele matricei indică dacă perechea de noduri corespunzătoare sunt sau nu adiacente în graf. (mai multe informații despre matricea de adicanță [^4])  

**De ce am ales 2 structuri de stocare a datelor?**  
```
Coada dublu-inlănțuită stochează și informațiile despre rute, în schimb ce matricea de adianență 
salvază unde există drum între două stații și maxim distanța între stații.
```
![alt text](https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/coada.jpeg)
<img src="https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/graf_neorientat.jpeg" style="width:600px;"/>
<img src="https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/graf_orientat.jpeg" style="width:600px;"/>


### Algoritmii aplicați în proiect
* Algoritmul **Dijkstra** pentru **Drumul de cost minim** l-am folosit pentru **a măsura distanța minimă de la o stație la altă stație** și am adăugat funcții recursive de afișare a rutei între stații. Am modificat algoritmul, astfel încât să funcționeze pentru aflarea drumului de cost **minim** sau **maxim**. 
* Algotirmul **Kruskal** scoate din graf: **Arbore minim de acoperire**, adică din toată rețeaua de cale ferată scoate „scheletul” ei: un **graf** în care oricare două stații sunt unite print-un singur drum. Algoritmul scoate acest graf **minim**: minimizează 10389 km cale ferată în 4727 km cale ferată, fără să scoată nicio stație! 
* Dacă vrem să găsim distanța minimă între București Nord și Galați, pe graful neorientat: 259 km. În schimb, în Minimum span tree (**m.s.t**): 1250 km și e singura rută.

### Utilizarea programului
Acum că am definit diferențele înte algoritmii Dijkstra și Kruskal, funcțiile aplicației sunt următoarele, rezultatele in **Output** sub formă text:
- Creez 5 grafuri:
  - Graf neorientat simplu
  - Graf neorientat cu cost => folosit pentru algoritmul Dijkstra și Kruskal
  - Graf orientat simplu
  - Graf orientat cu cost
  - Min span tree
- Rezultate Dijkstra:
  - **lungime_total.txt** <-Totalul de km de cale ferată
  - **dist_min_doua_statii.txt** <-Stațiile cu distanta cea mai mica și ruta
  - **dist_max_doua_statii.txt** <-Stațiile cele mai depărtate și linia
- Rezultate Kruskal:
  - **mst_dist_MIN_doua_statii.txt** <-Stațiile cu distanta cea mai mica și ruta
  - **mst_dist_MAX_doua_statii.txt** <-Stațiile cele mai depărtate și linia
- Rezultate User Input (graph la alegere)
  - **drum_cost_minim.txt** <-drumul de cost minim intre aceste doua orase (sau pur și simplu drumul între cele două stații dacă se alege m.s.t.)
  - **departe.txt** <-cea mai îndepărtată stație de stația sursă
  - **ruta_max.txt** <-cel mai lung drum (de cost minim)
- Altele:
  - **nr_muchii.txt** 
  - **nr_noduri.txt**

## Surse
Tema de laborator SDA: Dijkstra: https://ocw.cs.pub.ro/courses/sda-aa/laboratoare/09  
Kruskal: https://ocw.cs.pub.ro/courses/sda-aa/laboratoare/10  
[^1]: https://ro.wikipedia.org/wiki/Teoria_grafurilor
[^2]: https://ro.wikipedia.org/wiki/Algoritmul_lui_Dijkstra
[^3]: https://ro.wikipedia.org/wiki/Algoritmul_lui_Kruskal
[^4]: https://ro.wikipedia.org/wiki/Matrice_de_adiacen%C8%9B%C4%83


