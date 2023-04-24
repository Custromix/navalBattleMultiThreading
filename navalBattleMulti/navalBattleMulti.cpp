// navalBattleMulti.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Framework.h"

int main()
{
   
    App* BATTLENAVALMUTLI = new App();

    SetApp(BATTLENAVALMUTLI);

    BATTLENAVALMUTLI->Init();
    BATTLENAVALMUTLI->Start();
    return 0;

}

