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
  depth: 2,

)

#outline(
  title: [Liste des figures],
  target: figure.where(kind: image),
)

#pagebreak()

= Introduction

Ce papier vient rendre compte du développement et de l'implémentation de différents algorithmes dans le but de jouer au jeu de plateau d'Othello.

On détaillera par la suite l'implémentation du jeu en `C++`, les différentes classes et structures de données mises en place afin de communiquer avec les différentes intelligences artificielles. On présentera ensuite les intelligences qui ont pu être implémentées ainsi que les stratégies mises en place.

= Développement du jeu

== Classe `Board`

= Interfaces d'intelligence artificielle

== `AInterface.hpp`

== `Minmax.hpp`

== `AlphaBeta.hpp`