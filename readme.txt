Jeu prévu pour Linux

bibliothèques à installer: ncurses

commandes d'installation pour système type Debian:
sudo apt-get install libncurses5-dev libncursesw5-dev

Compilation et Lancement:
Depuis le dossier ProjetC, commande make pour compiler et commande bin/jeu.bin pour executer

--------------------------------------------------------------------------------------------

Projet C: Dorian Creuze et Max Descomps

Notre projet est un jeu en temps réel, rendu possible grâce à des compteurs
dans la structure de chaque entité, le type entité étant un type abstrait
(entite.c) regroupant les mobs, le personnage, les tirs et autre structures
similaires afin de simplifier le code et d'alléger la carte (un seul pointeur
sur entité générique par carré).

Des listes génériques doublement chaînées (liste.c) permettent de gérer les
tirs, les mobs, les coffres, les items dans les coffres car on ne connaît pas
leur nombre en avance et qu’ils peuvent être générés en masse. On
optimise ainsi la mémoire occupée par le programme en temps réel.

En revanche, l'inventaire est un tableau d’items car sa taille est raisonnable
et constante et que nous voulons accéder à un item donné instantanément
en appuyant sur la touche qui lui est attribuée (f1 à f10) sans parcourir à
chaque fois une liste. L’item sélectionné est mis en surbrillance.
(voir fenêtre d’inventaire en dessous de celle du jeu)

Le personnage ramasse un objet, un bloc et ouvre un coffre (représenté par un '$' orange) face à lui avec
la touche ‘e’. Il peut se déplacer dans le coffre avec les flèches
directionnelles gauche et droite, et récupérer un item avec la flèche du
haut.
(voir fenêtre de coffre lors de son ouverture en dessous de celle de
l’inventaire)

L’item est alors placé dans son inventaire.
Il peut l’utiliser avec ‘f’ (poser un bloc, se soigner avec un consommable
trouvé dans un coffre etc.).

Le personnage se déplace avec les touches ‘zqsd’ et ouvre sa mini carte des
zones explorées en appuyant sur ‘m’.
Il voit à une distance limitée et peut tirer des projectils modifiés selon son
niveau avec les flèches directionnelles.

Les tirs infligent des dégâts aux mobs (représentés par un '!') comme au personnage (représenté par une flèche), qui gagne de
l'expérience en tuant les mobs, avant de monter de niveau et de statistiques
(voir fenêtre de statistiques au-dessus de celle du jeu).

La carte est générée aléatoirement avec l’algorithme du bruit de Perlin
et les conditions de validité de création et lancement du jeu sont vérifiées
(input utilisateur, résolution…).
Des lacs, îles et océans de notre création sont ajoutés à la carte.

C’est un monde ouvert et l’affichage de la carte est dynamique : si le
joueur se déplace, il reste au centre de l’écran et la carte défile, mais s’il se
rapproche d’un bord de carte, c’est le joueur qui bouge et non la carte.
Ainsi, on ne voit jamais hors de la carte.
(Test facile avec une carte de taille 50)

Un premier menu au démarrage du jeu permet de créer un partie ou bien
d’en charger une depuis sa sauvegarde.
Le nom de la sauvegarde est le nom du joueur et il n’y a pas de doublon de
sauvegarde.

Des niveaux de difficulté sont implémentés, ils régulent l’hostilité des
mobs (1 = non-hostiles, 2 = normal, 3 = très hostiles)

Le niveau 3 est recommandé afin de se rendre compte des capacités du jeu.

Les mobs apparaissent hors vision à une cadence d’apparition donnée juste
après la vue du personnage et sont détruits si trop éloignés.

Les tirs ont une cadence et un temps de voyage configurables.

Le menu de pause dans lequel on navigue avec les flèches et on
sélectionne avec la touche entrée est accessible avec la touche ‘p’, et
permet de sauvegarder et/ou quitter. Le bouton ‘n’ permet aussi de quitter
directement en jeu.

Un menu permettant de quitter ou de relancer à la dernière sauvegarde
s’ouvre également lors de la mort du personnage.

L’affichage s’adapte dynamiquement à la taille de l’écran.

Certaines cases comme l’eau (représentée par un 'W' bleu) ou les entités sont inaccessibles.


Pour plus d’information, notament sur la liste des fichiers et la présentation de leur contenu,
le code est totalement documenté et un fichier Doxygen est généré sans erreur (doc/html/index.html)

Pour une utilisation normale du jeu, valgrind ne donne aucune fuite
mémoire sauf celles naturellement générées par la librairie ncurses
(commande `valgrind –leak-check=full bin/jeu.bin` pour plus de détails)