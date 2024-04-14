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
#set page(
  footer: locate(
      loc => {
        let page-number = counter(page).at(loc).first()
        let match-list = query(selector(<turn-on-page-numbering>).before(loc), loc)
        if match-list == () { return none }
        align(center, "— " + str(page-number) + " —")
      },
    ),
)

#show outline.entry: it => {
  if it.at("label", default: none) == <custom-entry> {
    it
  } else {
    [
      #outline.entry(
        it.level,
        it.element,
        it.body,
        it.fill,
        [#it.element.location().page()],
      ) <custom-entry>
    ]
  }
}

#show ref: it => {
  let el = it.element
  if el != none and el.func() == heading {
    el.body
  } else {
    it
  }
}

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
  depth: 2,
  indent: true
)

#pagebreak(weak: true)

#outline(
  title: [Liste des figures],
  target: figure.where(kind: figure),
)

#pagebreak(weak: true)

= Introduction <turn-on-page-numbering>

Ce papier vient rendre compte du développement et de l'implémentation de différents algorithmes dans le but de jouer au jeu de plateau d'Othello.

On détaillera par la suite l'implémentation du jeu en `C++`, les différentes classes et structures de données mises en place afin de communiquer avec les différentes intelligences artificielles. On présentera ensuite les intelligences qui ont pu être implémentées ainsi que les stratégies mises en place.

== Architecture du projet <architecture>

Le projet a été développé en C++, l'archive fournie contient donc les sources aux format `.cpp` dans le dossier `src` et les headers au format `.hpp` dans le dossier `includes`. Elle contient également un fichier `makefile` dans le but d'aider le lecteur à la compilation. Sinon cette dernière est possible de manière classique via `g++ src/*.cpp -o main -Iincludes`. Le dossier bin est utilisé pour stocker les fichiers objets lors de la compilation à l'aide de `makefile`.

L'architecture complète est celle présentée en @architecture_projet

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

Elle permet également de calculer différentes informations sur le plateau tel que les coups valides pour un joueur donné, leurs scores mais contient également les fonctions permettant de jouer un coup en vérifiant que celui-ci est valide et en retournant les pions à capturer.

=== Type `Pawn`

Le type Pawn servira à représenter un pion dans le reste des sources. Sa définition est reprise en @enum_pion.

#figure(
  rect(
    ```cpp
    typedef enum : unsigned short
    {
        EMPTY = 0,
        WHITE = 1,
        BLACK = 2,
    } Pawn;
    ```,
    inset: 10pt
  ),
  caption: "Enumération Pawn",
  kind: figure,
  supplement: "Figure"
) <enum_pion>

=== Type `Direction`

Le type `Direction` représentera une direction dans les fonctions de vérification de validité des jeux et de placement des pions. Sa définition est indiquée en @enum_dir.

#figure(
  rect(
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
    ```,
    inset: 10pt
  ),
  caption: "Enumération Direction",
  kind: figure,
  supplement: "Figure"
) <enum_dir>

=== Coeur de la classe

Le premier objectif de la classe `Board` est de sauvegarder l'état du plateau. Cette sauvegarde est effectuée dans un tableau à une dimension de type `Pawn`. Pour accéder à une case du tableau on effectuera donc l'opération : _ligne_ $*$ _taille_ $+$ _colonne_, c'est le rôle de la fonction `coordToIndex(const std::string& coord) const;` qui prend en paramètre une coordonnée litérale (i.e. "b3") et qui la convertit en un index valide du tableau (i.e. "17").

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

L'algorithme MinMax, maximise et minimise successivement ses coups et les coups de l'adversaire. Pour le jeu d'Othello il est néanmoins nécessaire de vérifier le joueur courrant étant donné qu'un même joueur peut jouer plusieurs fois successivement.

Le pseudo code de l'algorithme implémenté est celui de l'@algo_minmax

#algorithm(
    pseudocode-list(
      indentation-guide-stroke: stroke(thickness: .5pt),
    )[
      - *entrées:* _nœud_ ; _profondeur_ ; _coup_ ; _joueurMax_
      - *sortie:* valeur heuristique de _nœud_
      + *si* _profondeur_ $= 0$ *ou* _nœud_ est terminal *alors*
        + *retourner* heuristique(_nœud_)
      + *si* _joueurMax_ *alors*
        + _valeur_ $<- -oo$
        + *pour chaque* _coup_ possible de _nœud_ *faire*,
          + _enfant_ $<- $ joue(_coup_, _noeud_)
          + _valeur_ $<- $ max(_valeur_, minmax(_enfant_, _profondeur$-1$_, _coup_, FAUX))
          + *retourner* _valeur_
      + *sinon*
        + _valeur_ $<- +infinity$
        + *pour chaque* _coup_ possible de _nœud_ *faire*
          + _enfant_ $<- $ joue(_coup_, _noeud_)
          + _valeur_ $<- $ min(_valeur_, minmax(_enfant_, _profondeur$-1$_, _coup_, VRAI))
        + *retourner* _valeur_
    ],
    caption: [MinMax],
    supplement: "Algorithme"
) <algo_minmax>

#pagebreak(weak: true)

== `AlphaBeta.hpp`

L'algorithme AlphaBeta est une amélioration de l'algorithme MinMax. Il permet de réduire le nombre de nœuds explorés en élaguant les branches inutiles. Cette amélioration de l'algorithme précédent permet donc d'améliorer le temps d'exécution et de recherche.

Le pseudo-code de l'algorithme utilisé est présenté par l'@algo_alphabeta

#algorithm(
    pseudocode-list(
      indentation-guide-stroke: stroke(thickness: .5pt),
    )[
      - *entrées:* _nœud_ ; _profondeur_ ; $alpha$ ; $beta$ ; _joueurMax_
      - *sortie:* valeur heuristique de _nœud_
      + *si* _profondeur_ $= 0$ *ou* _nœud_ est terminal *alors*
        + *retourner* heuristique(_nœud_)
      + *si* _joueurMax_ *alors*
        + _valeur_ $ <- -infinity$
        + *pour chaque* _enfant_ de _nœud_ *faire*,
          + _valeur_ $<- $ max(_valeur_, alphabeta(_enfant_, _profondeur$-1$_, $alpha$, $beta$, FAUX))
          + *si* valeur $>=$ $beta$ *alors*
            + break
          + _$alpha$_ $<- $ max($alpha$, _valeur_)
        + *retourner* _valeur_
      + *sinon*
        + _valeur_ $<- +infinity$
        + *pour chaque* _enfant_ de _nœud_ *faire*
          + _valeur_ $<- $ min(valeur, alphabeta(_enfant_, _profondeur$-1$_, $alpha$, $beta$ , _VRAI_))
          + *si* _valeur_ $<=$ $alpha$ *alors*
            + break
          + _$beta$ $<- $ min($beta$,valeur_)
        + *retourner* _valeur_

      - *Premier appel* : alphabeta(_racine_, profondeur, -$infinity$, +$infinity$, VRAI)
    ],
  caption: [AlphaBeta],
  supplement: "Algorithme"
) <algo_alphabeta>

#pagebreak(weak: true)

= Stratégies

Les stratégies _positionnelle_, _absolue_, _mobilité_ et _mixte_ ont été implémentée pour les algorithmes MinMax et AlphaBeta.

L'algorithme choisit l'heuristique correspondant à la stratégie donnée en paramètre lors de son initialisation.

== Positionnelle

L'heuristique positionnelle calcule le score du noeud en se basant sur la matrice de récompense vu en @payoff_matrix. Le code est le suivant :

#figure(
  rect(
    ```cpp
    int MinMax::heuristic_pos(const Board &B) const
    {
        int score = 0;
        for (int i = 0; i < B.getSize(); i++)
        {
            for (int j = 0; j < B.getSize(); j++)
            {
                int c = i * B.getSize() + j;
                if (B.getCoord(c) == this->player)
                {
                    score += this->payoff_matrix[c];
                }
            }
        }
        return score;
    }
    ```,
    inset: 10pt
  ),
  caption: "Calcul heuristique positionnel",
  kind: figure,
  supplement: "Figure",
)

== Absolue

La stratégie absolue attribue une valeur au noeud en fonction du score du joueur. Le score étant représenté par le nombre de pions du joueurs correspondant, le code de l'heuristique est assez simple. Néanmoins on fera attention a la subtilité en fonction du joueur joué par l'algorithme pour ne pas avoir une valeur de noeud négative :

#figure(
  rect(
    ```cpp
    int MinMax::heuristic_abs(const Board &B) const
    {
        // Care to the sign for the operation
        if (this->player == Pawn::BLACK)
        {
            return B.getBlackScore() - B.getWhiteScore();
        }
        else
        {
            return B.getWhiteScore() - B.getBlackScore();
        }
    }
    ```
  ),
  caption: "Calcul heuristique absolu",
  kind: figure,
  supplement: "Figure"
)

== Mobilité

L'heuristique mobilité se sert du dernier pion placé pour prioriser les déplacements dans les coins du plateau en se basant sur la matrice de récompense pour retourner le score scorrespondant.

Si le déplacement n'est pas joué dans un coin alors la valeur est le nombre de déplacement possible.

#figure(
  rect(
    ```cpp
    int MinMax::heuristic_mob(const Board &B, std::string move) const
    {
      if (this->payoff_matrix[B.coordToIndex(move)] > 400)
      {
          return this->payoff_matrix[B.coordToIndex(move)];
      }

      if (B.getCurrentPlayer() == Pawn::BLACK)
      {
          return B.getValidMoves(B.getCurrentPlayer()).size() - B.getValidMoves(Pawn::WHITE).size();
      }

      return B.getValidMoves(B.getCurrentPlayer()).size() - B.getValidMoves(Pawn::BLACK).size();
    }
    ```,
  ),
  caption: "Calcul heuristique mobilité",
  kind: figure,
  supplement: "Figure"
)

= Utilisation du CLI

Une fois compilé (cf. @architecture), le programme peut être lancé en ligne de commande de la façon suivante:

#align(center)[
  ```
  othello BLACK WHITE [--depth-black PROFONDEUR] [--depth-white PROFONDEUR] [--benchmark MONTANT] [--display-grid] [--only-final]
  ```
]

#table(
  columns: (auto, auto),
  inset: 10pt,
  [BLACK],
  [
    Obligatoire. Interface jouant les pions noirs. Les valeurs possibles sont: `minmax`, `alphabeta`, `random` et `player`
  ],
  [WHITE],
  [
    Obligatoire. Interface jouant les pions blancs. Les valeurs possibles sont: `minmax`, `alphabeta`, `random` et `player`
  ],
  [`--depth-black PROFONDEUR`],
  [
    Profondeur personalisée pour l'algorithme jouant les pions noirs. Par défaut à 3, ignoré pour `player` et `random`.
  ],
  [`--depth-white PROFONDEUR`],
  [
    Profondeur personalisée pour l'algorithme jouant les pions blancs. Par défaut à 3, ignoré pour `player` et `random`.
  ],
  [`--benchmark MONTANT`],
  [
    Le programme joue autant de parties que `MONTANT` lui indique.
  ],
  [`--display-grid`],
  [
    Affiche les grilles de fin de partie pour la ou les parties jouées.
  ],
  [`--only-final`],
  [
    Affiche les résultats une fois que toutes les parties demandées ont été jouées. Remarque: Les accumulateurs statistiques sont uniquement affiché lorsque toutes les parties ont été jouées et non après chaque partie.
  ]
)

#pagebreak()

= Statistiques et Critiques

Comparons les différents algorithmes alimentés des différentes stratégies.

== Random - Random

Dans un premier temps vérifions que l'affrontement entre 2 algorithmes complètement aléatoire tend vers 1 partie gagnée sur 2 pour chaque joueur.

#figure(
  rect(
    ```
    $ ./main random random --benchmark 1000 --only-final
    Game 1000/1000

    ====== Résultats ======
    [NOIRS ] Victoires:    442 (44.2%)
    [BLANCS] Victoires:    518 (51.8%)
    [******] Egalités:      40 (4%)
    [EXEC  ] Temps moyen d'une partie: 0.887ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  49%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 50%
    ```
  ),
  caption: "Affrontement Random - Random sur 1000 parties",
  kind: figure,
  supplement: "Figure"
)

Malgré la proximité des 50% de parties gagnées pour les blancs, on peut néamoins remarquer un avantage pour ces derniers en jouant de manière totalement aléatoire. On peut potentiellement expliquer cet avantage comme étant dû à l'ordre de jeu. En effet, jouant en deuxième, les blancs peuvent capturer le pion joué par les noirs aux premier tour, offrant un potentiel un avantage.

== Minmax - Random

Ci-dessous sont détaillés différents résultats impliquant l'algorithme MinMax contre un algorithme complètement aléatoire.

Les tests présentés ont tous été effectuée sur 50 parties avec une profondeur de recherche de 5 coups.

=== Stratégie positionnelle

La stratégie positionnelle est la stratégie affichant les résultats les plus convainquants. Pour une profondeur de 5 l'algorithme MinMax ne perd quasiment aucune partie tant en jouant les noirs, @minmax_pos_black, qu'en jouant les blancs, @minmax_pos_white.

#figure(
  rect(
    ```
    $ ./main minmax random --depth-black 5 --strategy-black pos
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:     49 (98%)
    [BLANCS] Victoires:      1 (2%)
    [******] Egalités:       0 (0%)
    [EXEC  ] Temps moyen d'une partie: 16841.1ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  66%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 33%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement MinMax - Random sur 50 parties pour une stratégie positionnelle"
) <minmax_pos_black>

#figure(
  rect(
    ```
    $ ./main random minmax --depth-white 5 --strategy-white pos
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      2 (4%)
    [BLANCS] Victoires:     48 (96%)
    [******] Egalités:       0 (0%)
    [EXEC  ] Temps moyen d'une partie: 13651ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  35%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 63%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - MinMax sur 50 parties pour une stratégie positionnelle"
) <minmax_pos_white>

On remarque que le terrain occupé est en moyenne réparti avec la proportion 2 tiers 1 tier à l'avantage de l'algorithme MinMax

=== Stratégie absolue

#figure(
  rect(
    ```
    $ ./main minmax random --depth-black 5 --strategy-black abs
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:     43 (86%)
    [BLANCS] Victoires:      7 (14%)
    [******] Egalités:       0 (0%)
    [EXEC  ] Temps moyen d'une partie: 7583.37ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  59%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 27%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement MinMax - Random sur 50 parties pour une stratégie absolue"
)

#figure(
  rect(
    ```
    $ ./main random minmax --depth-white 5 --strategy-white abs
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      5 (10%)
    [BLANCS] Victoires:     44 (88%)
    [******] Egalités:       1 (2%)
    [EXEC  ] Temps moyen d'une partie: 14086.5ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  35%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 62%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - MinMax sur 50 parties pour une stratégie absolue"
)

=== Stratégie mobilité

La stratégie mobilité priorise les coins du plateau, étant considérés comme les emplacements les plus profitables et permettant d'engranger beaucoup de pions tout au long de la partie en reprenant ceux de l'adversaire. Lorsqu'elle ne peut jouer dans un coin la stratégie a pour but de minimiser les coups disponibles pour son adversaire en amximisant les siens.

Les résultats obtenus par MinMax jouant les noirs en utilisant cette stratégie sont présentés en @minmax_black_mob et ceux en jouant les blanc en @minmax_white_mob

#figure(
  rect(
    ```
    $ ./main minmax random --depth-black 5 --strategy-black mob
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:     34 (68%)
    [BLANCS] Victoires:     14 (28%)
    [******] Egalités:       2 (4%)
    [EXEC  ] Temps moyen d'une partie: 15858.5ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  58%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 41%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement MinMax - Random sur 50 parties pour une stratégie mobilité"
) <minmax_black_mob>

#figure(
  rect(
    ```
    $ ./main random minmax --depth-white 5 --strategy-white mob
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      3 (6%)
    [BLANCS] Victoires:     45 (90%)
    [******] Egalités:       2 (4%)
    [EXEC  ] Temps moyen d'une partie: 13721.5ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  37%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 61%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - MinMax sur 50 parties pour une stratégie mobilité"
) <minmax_white_mob>

Pour une stratégie minisant les coups disponibles pour l'adversaire et s'offrant une grande possibilité de jeu on devrait s'attendre à une occupationdu terrain plus accrue, c'est pourquoi nous émettons des doutes quand à la précision de notre heuristique.

Néanmoins des parties étouffant rapidement l'adversaire ont été joué en utilisant cette stratégie telle que celle en @ex_minmax_mob_1

#figure(
  rect(
    ```
    +-----------------------+
    | Résultat:      Blancs |
    |-----------------------|
    | Vide | Noirs | Blancs |
    |-----------------------|
    |   30 |     0 |     34 |
    +-----------------------+

    Grille de jeu:
      a b c d e f g h
    1 . . O O O . . . 
    2 . . O O O . . . 
    3 O O O O O . . . 
    4 O O O O O . . . 
    5 O O O O O O . . 
    6 O O O O O . . . 
    7 . O O . O O . . 
    8 O . O . . O . .
    ```,
    inset: 10pt
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Exemple de partie jouée par MinMax en utilisant une stratégie mobilité"
) <ex_minmax_mob_1>



=== Stratégie mixte

La stratégie mixte combine les trois stratégies vus précedemment. L'algorithme joue suivant la matrice de poids statistiques pour les 25 premiers coups, ensuite considère les coins en maximisant ses propres coups et minimisant ceux de son adversaire et joue les 22 derniers coups en maximisant son score et minimisant celui de l'adversaire.

Malgré les présumés défauts de notre heuristique de mobilité, la stratégie mixte affiche des résultat également convainquants en maitrisant une grande partie du plateau.

#figure(
  rect(
    ```
    $ ./main minmax random --depth-black 5 --strategy-black mixte
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:     44 (88%)
    [BLANCS] Victoires:      5 (10%)
    [******] Egalités:       1 (2%)
    [EXEC  ] Temps moyen d'une partie: 12724.4ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  65%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 33%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement MinMax - Random sur 50 parties pour une stratégie mixte"
)

#figure(
  rect(
    ```
    $ ./main random minmax --depth-white 5 --strategy-white mixte
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      3 (6%)
    [BLANCS] Victoires:     47 (94%)
    [******] Egalités:       0 (0%)
    [EXEC  ] Temps moyen d'une partie: 16227.5ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  34%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 65%
    ```,
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - MinMax sur 50 parties pour une stratégie mixte"
)

== AlphaBeta - Random

En utilisant l'élagage AlphaBeta les résultats sont similaire. L'élagage étant une amélioration de l'algorithme MinMax normalement le taux de victoire ne doit pas varier significativement. Néanmoins grâce à cet élagage on remarque que la durée moyenne des parties chute de 14/15 secondes pour l'algorithme MinMax à 5 secondes lorsque l'élagage alphabeta est utilisé, soit une division par presque 3.

Cette amélioration est donc non négligeable et extrèmement importante dans l'élaboration de telle algorithmes.

Ci-dessous les résultats obtenus pour AlphaBeta pour une stratégie positionnelle, @alphabeta_pos, une stratégie absolue, @alphabeta_abs, une stratégie mobilité, @alphabeta_mob, et une stratégie mixte, @alphabeta_mixte.

#figure(
  rect(
    ```
    $ ./main random alphabeta --depth-white 5 --strategy-white pos
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      7 (14%)
    [BLANCS] Victoires:     41 (82%)
    [******] Egalités:       2 (4%)
    [EXEC  ] Temps moyen d'une partie: 5063.58ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  38%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 61%
    ```
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - AlphaBeta sur 50 parties pour une stratégie positionnelle"
) <alphabeta_pos>

#figure(
  rect(
    ```
    $ ./main random alphabeta --depth-white 5 --strategy-white abs
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      6 (12%)
    [BLANCS] Victoires:     43 (86%)
    [******] Egalités:       1 (2%)
    [EXEC  ] Temps moyen d'une partie: 2537.22ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  26%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 72%
    ```
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - AlphaBeta sur 50 parties pour une stratégie absolue"
) <alphabeta_abs>

#figure(
  rect(
    ```
    $ ./main random alphabeta --depth-white 5 --strategy-white mob
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      7 (14%)
    [BLANCS] Victoires:     43 (86%)
    [******] Egalités:       0 (0%)
    [EXEC  ] Temps moyen d'une partie: 4963.3ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  30%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 68%
    ```
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - AlphaBeta sur 50 parties pour une stratégie mobilité"
) <alphabeta_mob>

#figure(
  rect(
    ```
    $ ./main random alphabeta --depth-white 5 --strategy-white mixte
    --benchmark 50 --only-final
    Game 50/50

    ====== Résultats ======
    [NOIRS ] Victoires:      2 (4%)
    [BLANCS] Victoires:     46 (92%)
    [******] Egalités:       2 (4%)
    [EXEC  ] Temps moyen d'une partie: 5092.83ms
    [EXEC  ] Occupation du terrain en moyenne par les noirs:  21%
    [EXEC  ] Occupation du terrain en moyenne par les blancs: 76%
    ```
  ),
  kind: figure,
  supplement: "Figure",
  caption: "Affrontement Random - AlphaBeta sur 50 parties pour une stratégie mixte"
) <alphabeta_mixte>

Malgré qu'AlphaBeta ne soit qu'un élagage de MinMax il semblerait que la moyenne du terrain occupé par ce dernier soit plus élevé (de l'ordre de 75% pour une stratégie mixte, @alphabeta_mixte et 70% pour une stratégie absolue, @alphabeta_abs) et cela même pour des échantillons de test plus grands. Il est raisonnable de penser que cela est donc potentiellement dû à la profondeur encore trop faible.

= Problèmes rencontrés

Le projet ayant été développé en `C++` la gestion mémoire a été une priorité pendant toute la durée du développement. Quelques accès mémoire non autorisés ont parfois freiné notre progression ainsi qu'une fuite mémoire lors des appels récursifs avec l'allocation des noeuds fils. Néanmoins nous ne regrettons pas ce choix étant donné qu'il nous a permis d'allouer manuellement nos objets pour nous permettre de gérer nous-même l'utilisation mémoire de notre programme.

= Perspectives d'amélioration et conclusion

Le projet est loin d'être optimal. Ici nous abordons quelques points qui, d'après notre point de vue, méritent d'être implémentés. Ces points permettrait d'améliorer les performances de calculs afin d'effectuer des analyses plus fines en poussant la profondeur de recherche ainsi que la taille de l'échantillon (respectivement de 5 et 50 dans les statistiques énoncées plus haut).

== Threading

Une première amélioration majeure à apporter est le threading de la recherche heuristique des algorithmes. En effet, de nos jours les ordinateurs possèdent de multiples coeurs et ne pas les utiliser nous prive d'une grande partie de la puissance de calcul disponible.

Un premier threading efficace pourrai être la création d'un thread par branche initiale de l'arbre de recherche. De cette façon on divise au premier tour par 4 la durée d'exploration de l'algorithme, et plus encore en milieu de partie. Cette amélioration permettrait également d'augmenter considérablement la profondeur de recherche.

== Affinement des heuristiques

Comme vu dans les statistiques l'heuristique de mobilité notamment ne montre pas de résultats assez convainquant, les statistiques d'occupation du terrain devraient être bien plus élevés pour un algorithme qui maximise ses coups et contrôles les coins du plateau.

Il serait également intéressant de faire varier les plages d'heuristiques pour la stratégie mixte ou d'en modifier l'ordre pour en analyser les évolutions.

== Pré-calcul de l'arbre de recherche

Afin d'optimiser davantage le temps de calcul et les performances du programme, un pré-calcul des noeuds et des coups à jouer en fonction pourrait être effectué moyennant un compromis sur le stockage de ces données.

Ce pré-calcul indiquerait pour tel noeud courrant le cuop optimal à jouer de manière immédiate sans calcul supplémentaire. Il pourrait être effectué sur les noeuds de début et de fin de partie, instants dans lesquels l'arbre de recherche se réduit.

== Implémentation de nouveaux algorithmes

Les algorithmes `minmax` et `alphabeta` sont des algorithmes déterministes, il est donc inutile d'y jouer plus d'une partie étant donné que ces dernières seront toutes identiques. Actuellement, le seul moyen de le départager reste de les faire jouer un nombre important de parties contre l'algorithme aléatoire et d'ensuite comparer les résultats.

Pour améliorer ce processus l'optimal serait d'implémenter un algorithme non déterministe tel qu'un algorithme de Monte-Carlo. Celui-ci s'exécuterai en un temps déterministe (non infini et non aléatoire) mais dont le résultat contient une part d'aléatoire. De cette façon les parties contre un algorithme déterministe ne seront jamais identiques et il sera possible de départager ces dernier de façon plus intéressante qu'avec un algorithme complètement aléatoire.

== Conclusion

