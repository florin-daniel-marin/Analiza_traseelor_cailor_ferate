# Analiza_traseelor_cailor_ferate
Acest proiect folosește structurile de date: **graph-uri și cozi(queue)** și algoritmii specifici graph-urilor: **Dijkstra și Kruskal** pentru analiza traseelor căilor ferate din România (doar traseele C.F.R.).  

Operațiile ce se pot face pe graph-uri includ: măsurarea drumului minim de la o stație la alta, măsurarea celui mai scurt drum/ celui mai lung, determinarea celui mai lung drum din rețea (fără a se vizita un drum dintre două stații de două ori). 

## Teoria Grafurilor
În matematică și informatică, teoria grafurilor studiază proprietățile grafurilor. Un graf este o mulțime de obiecte (numite **noduri**) legate între ele printr-o mulțime de **muchii** cărora le pot fi atribuite direcții (în acest caz, se spune că graful este **orientat**). Un graf poate fi reprezentat geometric ca o mulțime de puncte legate între ele prin linii (de obicei curbe). [^1]

## Dijkstra
Algoritmul lui Dijkstra este o metodă de a stabili drumul de cost minim de la un nod de start la oricare altul dintr-un graf. Numele este dat de Edsger Dijkstra, savantul care l-a descoperit. [^2]

## Kruskal
Algoritmul lui Kruskal este un algoritm în teoria grafurilor care  găsește submulțimea muchiilor care formează un arbore care include toate vârfurile și care este **minimizat** din punct de vedere al costului. Dacă graful nu este conex, atunci algoritmul găsește o pădure parțială de cost minim (un arbore parțial de cost minim pentru fiecare componentă conexă). Algoritmul lui Kruskal este un exemplu de algoritm greedy. [^3]

## Descrierea proiectului
* Rutele de tren se află în directorul **input**
* Rutele sunt citite din fișierele text și sunt introduse într-o structură de tip: **coadă dublu înlănțuită**. Din această coadă se creează apoi graf-urile.
* Graf-urile păstrează informația sub formă de matrice de adiacență
* Toate rezultatele sunt scrise în fișiere .txt în directorul **output**. Elementele matricei indică dacă perechea de noduri corespunzătoare sunt sau nu adiacente în graf. (mai multe informații despre matricea de adicanță [^4]) 
```
De ce am ales 2 structuri de stocare a datelor?  
Coada dublu-inlănțuită stochează și informațiile despre rute, în schimb ce matricea de adianență nu poate salva nr. rutei, doar faptul că există drum între 2 stații și măsura drumului în Km.
```
![alt text](https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/coada.jpeg)
![alt text](https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/graf_neorientat.jpeg)
![alt text](https://github.com/florin-daniel-marin/Analiza_traseelor_cailor_ferate/blob/main/images/graf_orientat.jpeg)

### Algoritmii aplicați în proiect
* Algoritmul **Dijkstra** pentru **Drumul de cost minim** l-am folosit pentru a măsura distanța minimă de la o stație la altă stație și am adăugat funcții recursive de afișare a rutei între stații. Am modificat algoritmul, astfel încât să funcționeze pentru aflarea drumului de cost **minim** sau **maxim**.
### 

## Surse
[^1]: https://ro.wikipedia.org/wiki/Teoria_grafurilor
[^2]: https://ro.wikipedia.org/wiki/Algoritmul_lui_Dijkstra
[^3]: https://ro.wikipedia.org/wiki/Algoritmul_lui_Kruskal
