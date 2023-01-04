
#include "bataille.h"

#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

int main()
{
//
    Bataille partie;
    partie.Initialisation();
    partie.Remplissage();
    partie.GenerBateau();
    partie.Affichage();
    //la partie se finit quand le nombre de bateaux coulés est de 3 pour l'ordinateur ou le joueur   
    while(partie.GetBateauCouleJ() < 3 && partie.GetBateauCouleO() < 3)
    {
        //methode pour deroule un tour 
        partie.Tour_J_O();
        cout << endl;
        //a chaque fin de tour, il y a un affichage de la grille ordinateur et joueur
        partie.Affichage();
    }
    cout << "--- FIN DE PARTIE" << endl << endl;
    partie.Affichage();
    if(partie.GetBateauCouleO() == 3){
        cout << "Le gagnant est le joueur." << endl;
    }
    else{
        cout << " le gagnant est l'ordinateur." << endl;
    }
	return 0;
}
