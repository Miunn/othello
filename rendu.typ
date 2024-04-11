#import "@preview/lovelace:0.2.0": *
#show: setup-lovelace

#set document(
  title: [Algorithmes de jeu de plateau à deux joueurs],
  author: ("Boudadi Liam", "Caulier Rémi"),
  keywords: ("IA", "intelligence artificielle", "Othello", "MinMax", "AlphaBeta"),
)
#set heading(
  numbering: "I.1.a.",
  depth: 3,
)

#image("assets/insahdf.jpg", width: 40%)

#align(center + horizon, text(17pt)[
  *Algorithmes de jeu de plateau à deux joueurs* 
])

#align(center + horizon, text(12pt)[
  Fondements de l'intelligence artificielle
])

#align(center + horizon, text(12pt)[
  Boudadi Liam, Caulier Rémi
])

#align(right + bottom)[
  #image("assets/uphf.png", width: 40%)
]

#pagebreak()

#outline(
  title: [Table des matières],
  depth: 3,
  indent: true
)

#outline(
  title: [Liste des figures],
  target: figure.where(kind: figure),
)

#pagebreak()

= Introduction

Ce papier vient rendre compte du développement et de l'implémentation de différents algorithmes dans le but de jouer au jeu de plateau d'Othello.

On détaillera par la suite l'implémentation du jeu en `C++`, les différentes classes et structures de données mises en place afin de communiquer avec les différentes intelligences artificielles. On présentera ensuite les intelligences qui ont pu être implémentées ainsi que les stratégies mises en place.

== Architecture du projet

Le projet a été développé en C++, l'archive fournie contient donc les sources aux format `.cpp` dans le dossier `src` et les headers au format `.hpp` dans le dossier `includes`. Elle contient également un fichier `makefile` dans le but d'aider le lecteur à la compilation. Sinon cette dernière est possible de manière classique via `g++ src/*.cpp -o main -Iincludes`. Le dossier bin est utilisé pour stocker les fichiers objets lors de la compilation à l'aide de `makefile`.

L'architecture complète est la suivante :

#figure(
  rect(
    width: 75%,
    inset: 15pt,
    align(left, ```
    Othello/
    |- bin/
    |  |- *.o
    |
    |- includes/
    |  |- AInterface.hpp
    |  |- Board.hpp
    |  |- Game.hpp
    |  |- MinMax.hpp
    |  |- AlphaBeta.hpp
    |  |- Random.hpp
    |  |- Player.hpp
    |- src/
    |  |- AInterface.cpp
    |  |- Board.cpp
    |  |- Game.cpp
    |  |- MinMax.cpp
    |  |- AlphaBeta.cpp
    |  |- Random.cpp
    |  |- Player.cpp
    |  |- main.cpp
    |
    |- makefile
    |- rendu.pdf
    ```)
  ),
  supplement: "Figure",
  kind: figure,
  caption: "Architecture du projet",
) <architecture_projet>

#pagebreak()

= Développement du jeu

La première étape avant l'implémentation d'algorithmes d'intelligences artificielles est le développement du jeu. Pour ce faire, deux classes principales ont été écrites : la classe `Board` et la classe `Game`. La classe `Board` gère le plateau d'une partie d'Othello tandis que la classe `Game` permet le bon déroulement d'une partie.

== Classe `Board`

En premier lieu, la classe `Board` définie deux types d'énumérations :

- Le type `Pawn`
- Le type `Direction`

=== Type `Pawn`

Le type Pawn servira à représenter un pion dans le reste des sources. Sa définition est :

```cpp
typedef enum : unsigned short
{
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
} Pawn;
```

=== Type `Direction`

Le type `Direction` représentera une direction dans les fonctions de vérification de validité des jeux et de placement des pions. Sa définition est :

```cpp
typedef enum : unsigned short
{
    NONE = 0,
    TOP = 1,
    RIGHT = 2,
    BOTTOM = 4,
    LEFT = 8,
    DTR = 16,
    DBR = 32,
    DBL = 64,
    DTL = 128,
} Direction;
```

=== Coeur de la classe

Le premier objectif de la classe `Board` est de sauvegarder l'état du plateau. Cette sauvegarde est effectuée dans un tableau à une dimension de type `Pawn`. Pour accéder à une case du tableau on effectuera donc l'opération : $op("ligne") * op("taille") + op("colonne")$, c'est le rôle de la fonction `coordToIndex(const std::string& coord) const;` qui prend en paramètre une coordonnée litérale (i.e. "b3") et qui la convertit en un index valide du tableau (i.e. "17").

La classe intègre également le joueur qui doit actuellement jouer (via le champ `Pawn currentPlayer`), cela permettra aux modèles IA d'effectuer les calculs (minimisation et maximisation par exemple) de manière cohérente avec le joueur courant étant donné qu'un même joueur peut jouer plusieurs fois à la suite.

Enfin la classe gère possède la fonction `bool play(const std::string& coord);` qui place le pion du joueur courant à la coordonnée donnée. Cette fonction, si la coordonnée est valide (dans les bornes du plateau, à un emplacement vide, en respectant les conditions de placement), capture les pionts adverses et met à jour le joueur courant grâce à la fonction `void togglePlayer();`.

La fonction `togglePlayer` passe au joueur suivant, si ce dernier ne peut pas jouer, elle change de nouveau de joueur mais ne vérifie pas si après ce deuxième changement, le joueur peut jouer. Cette vérification est laissée à la classe `Game` qui s'occupe de gérer le bon déroulement d'une partie.

== Classe `Game`

La classe `Game` initialise une instance de `Board` et possède deux fonctions principales :

#align(center)[
  ```cpp
  void startGame(const AInterface& interface1, const AInterface& interface2)
  ```
]
et

#align(center)[
  ```cpp
  Pawn analyseGame(bool verbose, bool displayGrid) const
  ```
]

La fonction `startGame` prend en paramètre deux interfaces d'intelligence artificielle (détaillées ci-après) correspondant au joueur noir et au joueur blanc et joue la partie.

La fonction `analyseGame` s'apelle lorsque la partie instanciée avec la classe `Game` est terminée. Cette fonction permet l'affichage de différentes statistiques telles que le gagnant, le nombre de pions capturés et la durée de la partie. Si le paramètre `displayGrid` est égal à `true` la fonction affiche également la grille finale.

= Interfaces d'intelligence artificielle

Afin d'implémenter différents algorithmes d'intelligence artificielle au sein du programme nous avons en premier créé une classe mère disposant de la déclaration commune des différents attributs et fonctions dont chaque algorithme doit diposer.

Cette définition générale correspond à la classe `AInterface` dont la déclaration se trouve dans le fichier `AInterface.hpp`.

== `AInterface.hpp`

Le standard définit par la classe `AInterface` contient les méthodes :

- ```cpp
virtual std::string play(const Board& board) const = 0;
```
- ```cpp
Pawn getPlayer() const;
```
- ```cpp
void showScores() const;
```

La fonction `play()` est décrite comme fonction virtuelle non définie dans le code de classe puisqu'elle est destinée à être implémentée dans les différents algorithmes d'intelligence.

La présence de cette fonction dans l'interface permet à la classe `Game` de l'appeler sans se soucier de l'algorithme utilisé.

Et les attributs :
- ```cpp
Pawn player;
```
- ```cpp
Pawn ennemy;
```
- ```cpp
Strategy strategy;
```
- ```cpp
int payoff_matrix[64];
```

La variable `payoff_matrix` correspond à la matrice des poids statistiques d'une grille `8x8`, ici nous utilisons la matrice présentée par la @payoff_matrix

#figure(
  $ mat(
          500, -150, 30, 10, 10, 30, -150,  500;
          -150, -250,  0,  0,  0,  0, -250, -150;
            30,    0,  1,  2,  2,  1,    0,  30;
            10,    0,  2, 16, 16,  2,    0,  10;
            10,    0,  2, 16, 16,  2,    0,  10;
            30,    0,  1,  2,  2,  1,    0,  30;
          -150, -250,  0,  0,  0,  0, -250, -150;
          500, -150, 30, 10, 10, 30, -150,  500;
  ) $,
  supplement: "Figure",
  kind: figure,
  caption: "Matrice de poids statistiques utilisée",
) <payoff_matrix>

== `Minmax.hpp`



== `AlphaBeta.hpp`

#figure(
  algorithm(
    caption: [AlphaBeta],
    pseudocode(
      no-number,
      [*entrées:* _nœud_ ; _profondeur_ ; alpha ; beta ; _joueurMax_],
      no-number,
      [*sortie:* valeur heuristique de _nœud_],
      [*si* _profondeur_ $= 0$ *ou* _nœud_ est terminal *alors*], ind,
        [*retourner* heuristique(_nœud_)], ded,
      [*si* _joueurMax_ *alors*], ind,
        [_valeur_ $ <- -∞$],
        [*pour chaque* _enfant_ de _nœud_ *faire*], ind,
          [_valeur_ $<- $ max(valeur, alphabeta(_enfant_, profondeur$-1$, $alpha$, $beta$, Faux))], ded,
          [_$alpha$_ $<- $ max($alpha$, _valeur_)],
          [*si* valeur $>=$ $beta$ *alors*], ind,
            [break], ded,
        [*retourner* _valeur_],ded,
      [*sinon*], ind,
        [_valeur_ $<- +∞$],
        [*pour chaque* _enfant_ de _nœud_ *faire*], ind,
          [_valeur_ $<- $ min(valeur, alphabeta(_enfant_, profondeur$-1$, $alpha$, $beta$ , Vrai))],
          [_$beta$ $<- $ min($beta$,valeur_)],
          [*si* valeur $<=$ $alpha$ *alors*], ind,
            [break], ded,ded,
      [*retourner* _valeur_]
  )
),
  supplement: "Figure",
  kind: figure,
  caption : [Algorithme AlphaBeta]
)

= Stratégies

Les stratégies _positionnelle_, _absolue_, _mobilité_ et _mixte_ ont été implémentée pour les algorithmes MinMax et AlphaBeta.

L'algorithme choisit l'heuristique correspondant à la stratégie donnée en paramètre lors de son initialisation.

== Positionnelle

== Absolue

== Mobilité

= Statistiques

Comparaison des différentes stratégies et algorithmes mis en place.

= Problèmes rencontrés

= Perspectives d'amélioration

= Conclusion

