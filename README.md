  

# TP Qt 1 - Alcooltest - Eliott MAUBERT

  

Conception d'une application simple avec Qt.
![Image montrant l'interface](https://i.ibb.co/jw02MXT/Screenshot-2023-12-17-162948.png)

## Prérequis

- Pour visualiser ce readme je vous conseille d'aller sur [https://stackedit.io/](https://stackedit.io/app#)

  

## Comportement de l'interface

  

- Le bouton effacer sert à effacer le contenu de tout les QLineEdit et du résultats. Concretement le bouton effacer revient à une interface comme au premier lancement

  

- Le bouton valider est actif que si le champ de saisie est différent de 0 ou n'est pas valide

  

- Un QlineEdit vide est assimilé à une valeur 0.

  

- Un clic sur le bouton « Valider » fait apparaître le QLabel de résultat avec un fond vert si le taux d’alcoolémie est inférieur au taux légal et en rouge sinon.

  

- On peut saisir que des chiffres dans les QLineEdit

  

- Le sexe Homme est selectionné par défaut au lancement de l'application


- Lors de l'affichage le taux d'alcool est afficher avec deux chiffre après la virgule

  

## Calcul du Taux d'Alcoolémie dans le Sang

  

La formule utilisée pour calculer le taux d'alcoolémie dans le sang est basée sur la formule de Widmark, qui prend en compte la quantité d'alcool consommée, le degré d'alcool, la masse de la personne et son sexe.

  

La formule est la suivante :

  

$$C = \frac{{Q \times D \times 0.789}}{{M \times r}}$$

  

où :

- \( C \) est le taux d'alcoolémie dans le sang (exprimé en g/L),

- \( Q \) est la quantité d'alcool consommée (en grammes),

- \( D \) est le degré d'alcool de la boisson consommée (en pourcentage),

- \( M \) est la masse de la personne (en kilogrammes),

- \( r \) est le coefficient de Widmark qui dépend du sexe de la personne (0.7 pour les hommes, 0.6 pour les femmes).

 [0.789](https://fr.wikipedia.org/wiki/%C3%89thanol) correspond à la masse volumique de l'alcool pour une température ambiante de 20°
