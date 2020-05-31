# BE_Board
simple simulation of an arduino board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Unité d'arrosage automatique mobile :

Arrosage automatique en fonction de la température, pression, humidité, luminosité, heure, programmation et commande externe.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    .Programme
Compilation à l'aide de g++ : "g++ -Wall -Wextra -std=c++11 -pthread board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino"
→ Run du système avec le fichier arduino

    .Simulation
Compilation à l'aide de g++ : "g++ -Wall -Wextra -std=c++11 simulateur.cpp -o simulateur"
→ Run du simulateur avec le fichier simulateur

Variables de l'environnement globales, internes au fichier mydevices.cpp
Commande externe (bouton d'arrosage manuel) : glisser un fichier "ON.txt" dans le répertoire

