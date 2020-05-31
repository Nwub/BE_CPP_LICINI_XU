# BE_Board
simple simulation of an arduino board

## Unité d'arrosage mobile

Arrosage automatique en fonction de la température, la luminosité et l'humidité  
Arrosage manuel possible par l'utilisateur

### Programme
Compilation à l'aide de g++ : `g++ -Wall -Wextra -std=c++11 -pthread board.cpp core_simulation.cpp mydevices.cpp sketch_ino.cpp -o arduino`  
→ Run du système avec le fichier arduino(.exe) : `./arduino`

### Simulation
Changement manuellement des variables globales dans _board.cpp_ pour modifier les conditions initiales de l'environnement

### Intéraction
Commande externe par l'utilisateur : glisser un fichier dans le répertoire _src_ avec pour nom l'un des suivant

#### système d'arrosage
→ "on.txt" : activation manuel  
→ "summer.txt" : activation automatique en mode été  
→ "winter.txt" : activation automatique en mode hiver  
→ "period.txt" : activation automatique en mode périodique  
→ sans fichier ou autre nom : désactivation de l'arrosage

#### ressources du système
→ "power.txt" : rechargement de la batterie  
→ "water.txt" : rechargement de l'eau  

_N.B. : augmentation de 3 devices supplémentaire par rapport à la version de base_