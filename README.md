# BE_Board
simple simulation of an arduino board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Unité d'arrosage mobile**

Arrosage automatique en fonction de la température, la luminosité, l'humidité, le mode
Arrosage manuel possible par action de l'utilisateur

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    .Programme
Compilation à l'aide de g++ : "g++ -Wall -Wextra -std=c++11 -pthread board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino"
→ Run du système avec le fichier arduino : ./arduino

    .Simulation
Changement manuellement des variables globales dans board.cpp pour modifier les conditions initiales de l'environnement

    .Intéraction
Commande externe par l'utilisateur : glisser un fichier dans le répertoire src avec pour nom l'un des suivant
`système d'arrosage`
→ "on.txt" : activation manuel
→ "summer.txt" : activation automatique en mode été
→ "winter.txt" : activation automatique en mode hiver
→ "period.txt" : activation automatique en mode périodique
→ sans fichier ou autre nom : désactivation de l'arrosage
`ressources du système`
→ "power.txt" : rechargement de la batterie
→ "water.txt" : rechargement de l'eau

N.B. : augmentation de 3 devices supplémentaire par rapport à la version de base