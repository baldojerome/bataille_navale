#ifndef BATAILLE_H
#define BATAILLE_H

#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

//////JUSTIFICATION CHOIX TABLEAU////////
/*j'ai utilise des tableaux en double dimension non dynamique 
pour la generation des grilles du joueur et de l'ordinateur.
En effet il n'est pas specifie dans l'enonce d'utiliser 
des pointeurs ou du referencement.
De plus nous sommes sur une approche non dynamique 
car les grilles ne changent pas de dimensions durant la partie.
Les bateaux doivent etre localises sur les grilles.*/
//////////////////////////

//////ETAT DES LIEUX////////

/*j'ai realise des methodes de controles sur les inputs du joueurs 
mais aussi pour eviter la redondance aux niveaux des coordonnees aleatoires 
pour l'ordinateur.*/

//////////////////////////

class Bataille
{
private:
//tableau du joueur
int tableauJ[5][5]; 
//tableau de l'ordinateur
int tableauO[5][5];
//nombre bateau joueur coulé
int bateauCouleJ;
//nombre bateau ordi coulé
int bateauCouleO;
//nombre de tours 

public:
    Bataille();
    ~Bataille();
    int GetBateauCouleJ();  
    int GetBateauCouleO();
    void SetBateauCouleJ();
    void SetBateauCouleO();
    void Initialisation();
    int GenerationCoordonnee();
    void GenerBateau();
    void PositBateauJ();
    int VerifInPut();
    void PositBateauO();
    void Remplissage();
    void Affichage();
    void Tour_J_O();
    void Tir_J_O(int tableau[5][5], int x, int y);
};

#endif // BATAILLE_H

Bataille::Bataille(){
    this->bateauCouleJ = 0;
    this->bateauCouleO = 0;
}

Bataille::~Bataille(){
    
}

int Bataille::GetBateauCouleJ(){
    return bateauCouleJ;
}

int Bataille::GetBateauCouleO(){
    return bateauCouleO;
}

//setter incrementant de 1 les compteur des bateaux coules 
//cette methode ne realise que cette operation
void Bataille::SetBateauCouleJ(){
    this->bateauCouleJ += 1;
}

//setter incrementant de 1 les compteur des bateaux coules 
//cette methode ne realise que cette operation
void Bataille::SetBateauCouleO(){
    this->bateauCouleO += 1;
}

void Bataille::Initialisation(){
    
    cout << "--- initialisation" << endl;
    cout << "LEGENDE" << endl;
    cout << "    INCONNU     : 0" << endl;
    cout << "    EAU         : 8" << endl;
    cout << "    BATEAU      : 9" << endl;
    cout << "    COULE       : 1" << endl;
    cout << endl;
    
}
//methode qui genere X ou Y d'une coordonnee
//elle est utilisee par PositBateauO() et Tour_J_O()
int Bataille::GenerationCoordonnee(){
        random_device rd;
        default_random_engine eng(rd());
        uniform_int_distribution<int> distr(0, 4);
        int gene = distr(eng);
        
        return gene;
}
//methode qui alloue la position de l'ensemble des bateaux ordinateur et joueur
//Elle utilise la methode PositBateauJ() et PositBateauO()
void Bataille::GenerBateau(){
    
    //generation et inclusion des bateaux joueur sur la grille 
    cout << "Entrez les coordonnees du 1er bateau" << endl;
    //appel methode Posit Bateau
    this->PositBateauJ();
    //inclure le 1er bateau (changement avec la case)
    cout << "Entrez les coordonnees du 2er bateau" << endl;
    this->PositBateauJ();
    //inclure le 2e bateau (changement avec la case)
    cout << "Entrez les coordonnees du 3er bateau" << endl;
    //inclure le 3e bateau (changement avec la case)
    this->PositBateauJ();
    cout << endl;
    cout << "C'est au tour de l'ordinateur de positionner ces bateaux" << endl;
    //utilisation de la methode PositBateauO() dans une  boucle pour generer les 3 bateaux
    for(int i = 0; i < 3 ; i++)
    {
        this->PositBateauO();
    }
    
    cout << endl << endl;
}

//methode qui implémente la position d'1 bateau ordinateur 
//Elle utilise la methode GenerationCoordonnee() pour generer les coordonnees pour l'ordinateur
void Bataille::PositBateauO(){
    int x = 0;
    int y = 0;
    x = this->GenerationCoordonnee();
    y = this->GenerationCoordonnee();
    
    if(this->tableauO[y][x] == 9){
        this->PositBateauO();
    }
    else{
        this->tableauO[y][x] = 9;
    }
}

//methode qui implémente la position d'1 bateau joueur
//methode qui utilise la methode VerifInput() pour les entrees du joueur
void Bataille::PositBateauJ(){
    
    
    int x = 0;
    int y = 0;
    cout << "X= ";
    x = this->VerifInPut();
    cout << "Y= ";
    y = this->VerifInPut();
    
    if( this->tableauJ[y][x] == 9){
        cout << "coordonnees deja utilisees, reprendre de nouvelles coordonnees" << endl;
        this->PositBateauJ();
    }
    else{
        this->tableauJ[y][x]= 9;
    }
}

//methode qui verifie l'input donne par joueur 
// si nombre < 0 et nombre > 4 alors il redemande
//methode utilisant de la recursivite
int Bataille::VerifInPut(){
    int genePoint = 0;
    cin >> genePoint;
    if(genePoint < 0 || genePoint > 4){
        cout << "Tapez un nombre compris entre 0 et 4 inclus" << endl;
        this->VerifInPut();
    }
    else
    {
       return genePoint; 
    }
}

//methode pour remplir la grille joueur ou ordinateur. 
//methode qui ne prend pas en compte la position des bateaux
//simplement une initialisation
void Bataille::Remplissage(){
    for(int i = 0; i < 5 ; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            this->tableauJ[i][j] = 0;
            this->tableauO[i][j] = 0;
        }
    }
}

//methode pour afficher les grilles joueur et ordinateur 
//methode qui montre à l'instant T l'ensemble des coups deja joues par les deux parties 
void Bataille::Affichage(){

    cout << "    ORDINATEUR";
    cout << "   JOUEUR" << endl;
    cout << "    ";
    for(int a = 0; a < 5 ; a++)
    {
        cout << a << " ";
    }
    cout << "   ";
    for(int b = 0; b < 5 ; b++)
    {
        cout << b << " ";
    }
    cout << endl;
    cout << endl;
    for(int i = 0; i < 5 ; i++)
    {
        cout << i << "   ";
        for(int j = 0; j< 5; j++)
        {
            cout << this->tableauO[i][j] << " ";
        }
        cout << "   ";
        for (int q = 0 ; q< 5; q++)
        {
            cout << this->tableauJ[i][q] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//methode qui joue le tour du joueur puis celui de l'ordinateur
//cette methode utilise la methode VerifInput pour verifier les entrees du joueur
//cette methode utilise la methode Tir_J_O qui realise le tir pour l'ordinateur ou le joueur
//Utilisation de la methode GenerationCoordonnee() pour generer coordonnees du tir de l'ordinateur
void Bataille::Tour_J_O(){
    
    int x; 
    int y;
  
    cout << "--- TOUR DU JOUEUR" << endl;
    cout << "Entrez une coordonnee valide pour x : ";
    x = this->VerifInPut();
    cout << "Entrez une coordonnee valide pour y : ";
    y  = this->VerifInPut();
    //tir avec coordonnees 
    this->Tir_J_O(this->tableauO, x, y);
    cout << endl;
        
    cout << "--- TOUR DE L'ORDINATEUR" << endl;
    x = this->GenerationCoordonnee();
    y = this->GenerationCoordonnee();
    this->Tir_J_O(this->tableauJ, x, y);
    cout << endl;
}

//methode qui initie le tir de l'ordinateur ou du joueur 
//avec les coordonnees la methode va verifier la case et annoncer le resultat du tir 
//si bateau(9) = bateau coule + incremente de 1 le compteur ordi ou joueur
void Bataille::Tir_J_O(int tableau[5][5],int x, int y){
    // avec coordonnees  va verifier la case et annoncer le tir 
    if(tableau == this->tableauJ)
    {
        if(this->tableauJ[y][x] == 0)
        {
            cout << "TIR A L'EAU a " << x << "-" << y << endl;
            this->tableauJ[y][x] = 8;
        }
        else if (this->tableauJ[y][x] == 9)
        {
            cout << "BATEAU COULE a " << x << "-" << y << endl;
            this->tableauJ[y][x] = 1;
            this->SetBateauCouleJ();
        }
        else if(this->tableauJ[y][x] == 1)
        {
            cout << "BATEAU DEJA COULE a " << x << "-" << y << endl;
        }
        else
        {
            cout << "ATTENTION COORDONNEES DEJA UTILISES" << endl;
        }
    }
    else
    {
        if(this->tableauO[y][x] == 0)
        {
            cout << "TIR A L'EAU a " << x << "-" << y << endl;
            this->tableauO[y][x] = 8;
        }
        else if (this->tableauO[y][x] == 9)
        {
            cout << "BATEAU COULE a " << x << "-" << y << endl;
            this->tableauO[y][x] = 1;
            this->SetBateauCouleO();
        }
        else if(this->tableauO[y][x] == 1)
        {
            cout << "BATEAU DEJA COULE a " << x << "-" << y << endl;
        }
        else
        {
            cout << "ATTENTION COORDONNEES DEJA UTILISES" << endl;
        }
    }
}