/*Duminica Ana-Maria - 312CC*/

Pentru aceasta tema am realizat cerinta 1. 
Am definit mai intai doua structuri: nod si muchie. Structura nod reprezinta 
un nod dintr-un graf si contine urmatoarele campuri: nr, ce stocheaza numarul 
nodului din graf, denumire, ce reprezinta numele nodului sau obiectivul din 
oras, asa cum este definit in cerinta si edges care este un pointer catre o 
structura muchie, reprezentand lista de muchii asociata nodului. 
Structura muchie reprezinta o muchie din graf si contine: pointer-ul dest catre 
un nod, destinatia muchiei, cost, ce stocheaza costul asociat muchiei si next ce 
este un pointer catre urmatoarea muchie din lista de muchii ale nodului.

Functia DFS este o functie recursiva care parcurge in adancime graful pornind de 
la un nod dat. Parametrii functiei sunt: variabila de tip int node ce reprezinta 
nodul de la care incepe parcurgerea, vectorul viz ce arata daca un nod a fost 
vizitat sau nu si vectorul de noduri oras. Marchez nodul de inceput ca vizitat 
Obtin lista de vecini ai nodului si cu ajutorul unui while iterez lista pana 
cand ajung la final. Obtin numarul nodului vecin si daca vecinul nu a fost 
vizitat atunci apelez iar functia recursiv si actualizez pointerul pentru a 
trece la urmatorul vecin.

Functia numar_grafuri calculeaza numarul de componente conexe din graful din 
vectorul oras. Parametrii functiei sunt: vectorul de noduri oras, variabila 
nr_noduri ce reprezinta numarul total de noduri din vector. Initializez vectorul 
viz de dimensiune nr_noduri cu 0 deoarece niciun nod nu a fost vizitat inca. 
Declar o variabila numar_grafuri cu 0 ce reprezinta numarul de elemente conexe 
din graf. Cu un for parcurg fiecare nod din graf si daca acesta nu a fost 
vizitat atunci apelez funtia DFS pentru a parcurge in adancime graful incepand 
de la acel nod. Incrementez numar_grafuri si continui mai departe pentru a gasi 
un nod nevizitat. La final returnez numarul de grafuri. 

Functia prim implementeaza algoritmul Prim pentru a calcula costul minim al unei 
componente conexe din graf. Functia primeste ca parametrii vectorul de tip nod, 
oras, numarul total de noduri din graf, si nodul de pornire. Mai intai 
initializez toate distantele cu o valoare mare, predecesorii sunt initializati 
cu -1 pentru a indica ca nu exista si toate nodurile sunt marcate ca fiind 
nevizitate. Setez distanta nodului de pornire cu 0 si intr-o bucla infinita 
gasesc nodul nevizitat cu cea mai mica distanta si il atribui variabilei u. 
Daca nu exista noduri nevizitate se iese din bucla. Daca exista noduri 
nevizitate, atunci se marcheaza nodul u ca vizitat, iar apoi pentru fiecare 
vecin al lui u verific daca a fost vizitat si daca costul muchiei este mai mic 
decat distanta curenta. Initializez cost minim cu 0 si pentru fiecare nod adaug 
la cost minim distanta corespunzatoare predecesorului sau. Returnez cost minim.

Functia primCostMinim primeste ca parametrii graful oras, numarul total de 
noduri, numarul de grafuri si un pointer catre fisierul in care vor fi scrise 
costurile minime ale componentelor conexe. Intai initializez vectorul viz cu 0 
pentru a marca toate nodurile ca nevizitate si vectorul cost cu 0.
Parcurg fiecare nod din graf si daca un nod este nevizitat atunci apelez functia 
DFS pentru a parcurge in adancime componenta conexa. Mai apoi incrementez 
numarul de grafuri si apelez functia prim pentru a calcula costul minim al 
componentei conexe curente si adaug valoarea in vectorul cost. Dupa aceea sortez 
cu ajutorul functiei bubbleSort vectorul de costuri pentru a fi in ordine 
crescatoare si scriu valorile in fisier.

Pentru functia bubbleSort parcurg vectorul de la inceput la sfarsit si compar 
elementul curent cu urmatorul. Daca elementul curent este mai mare atunci 
interschimb valorile. Procesul continua pana cand tot vectorul este sortat. 

In main, am definit prima data cerinta problemei ca primul argument. Dupa aceea 
am deschis fisierul si am citit din acesta numarul de noduri si numarul de 
muchii ale grafului. Mai apoi, am definit un vector de structuri de numar de 
noduri de elemente numit oras. Dupa aceea am initializat toate muchiile acestor 
noduri cu NULL. Initializez variabila nod cu 0, aceasta va fi utilizata pentru a 
numara numarul de noduri din graf. Dupa aceea cu un for citesc din fisier 
fiecare muchie cu nodurile corespunzatoare si costul acesteia. Initializez doua 
variabile cu -1 pentru a verifica daca nodul respectiv a fost adaugat in 
vector sau nu. Daca nu a fost adaugat, atunci adaug nodul in vector si iterez 
variabila nod pentru a trece la urmatorul. Apoi creez o muchie si o adaug in 
lista de vecini pentru primul nod, dar si pentru al doilea intrucat graful este 
neorientat. In final, apelez functia numar_grafuri si stochez rezultatul in 
varabila nr_grafuri. Dupa care deschid fisierul si scriu numarul de componente 
conexe din graf. 