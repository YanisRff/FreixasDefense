# Projet TowerDefense CIR2
Le but de notre jeu est de survivre le plus longtemps possible fasse à des vagues d'enmemis divers et de plus en plus nombreux au cours du temps tout en protégeant votre château.
Pour ce faire, vous pouvez acheter des tours de différent type et niveau contre de l'or qui vous serviront à tenir votre position.

## I. Comment jouer
### Ennemis
Ils sont de divers natures et possèdent des caractéristiques différentes. Ceux de base: Squelettes, Zombies et Gobelins sont peu résistants et infligeront peu de dégât à votre château. Toutefois, ils peuvent apparaîtrent en masse et facilement vous submerger. Ceux de niveau intermédiaire: Gargouilles, Orcs, Necromanciens et Goules sont déjà plus résistants. Les goules sont fragiles mais très rapides et les Orcs lents mais très résistants. Enfin, parmi les ennemis les plus coriaces, vous retrouverez le Mage, le Commandant, et le grand Freixas. Ceux-ci sont très rares mais lorsqu'ils arrivent sur le plateau, ils peuvent facilement tout détuire !

### Tours
Pour vous défendre, différentes tours sont à votre disposition en échange de quelques pièces d'or. La Tour Classique est le parfait compromis entre dégâts, portée et coût de construction. Elle pourra vous fournir dès le début une bonne protection. Cependant, lorsque la difficulté se corsera, vous voudrez probablement diversifier vos défenses. La Tour Tesla vous permettra d'attaquer très rapidemment plusieurs cibles en même temps. La Tour à Canon inflige quant à elle de lourds dégâts à intervalle plus long. Enfin la Tour d'Arbalète bénéficie d'une grande portée et de dégâts moyens. Chaque niveau de tour augmente toutes ses statistiques et vous permettront de tenir le plus longtemps fasse aux vagues d'ennemis.

### Vagues
Les vagues augmentent en difficulté toutes les trente secondes. Plus d'ennemis apparaîtront en particulier ceux de classe supérieure. Toutes les dix secondes, une poignée d'ennemis apparaît.

### Commandes essentielles:
- __Clique Droit__ pour ouvrir le menu d'achat des tours.
- __Double Clique Gauche__ pour acheter une tour et __Clique Gauche__ pour la placer en jeu.
- __La molette__ et __les flèches directionnelles__ vous permettront de zoomer et de vous déplacer dans la scène de jeu.
- __R__ pour remettre la vue à sa position d'origine.
- Appuyez sur __S__ pour vendre les tours dans leur ordre de placement!
- Cliquez sur le menu "Game" puis "Restart" pour redémarrer la partie en cas d'échec.

 ## II. Compilation
Afin de compiler le code source et de pouvoir lancer le jeu, voici les étapes à suivre.

### Dépendance QT
Veillez à utiliser la même version de QT que celle renseignée dans le fichier CMakeList.txt. Nous avons utilisé QT5 par défaut.
Vous pouvez au besoin modifier de vous-même la version de QT du projet pour correspondre avec la vôtre.

### Avec CMake
CMake est un outil très pratique qui permet de lier automatiquement les fichiers et dépendances entre eux. C'est la méthode que nous recommandons pour ce projet.
1. Installer CMake et Make sur votre distribution (selon votre gestionnaire de paquets):
```sudo apt install cmake``` puis
```sudo apt install make```
2. Télécharger le code source depuis le repos git et déplacer vous dans le répertoir courant:
```cd ~/.../TowerDefenseYanisNirina```
3. Nettoyez le répertoir en cas de compilation antérieure:
```make clean && make distclean```
4. Créez un répertoire temporaire pour la construction du projet:
```mkdir build-dir```
5. Déplacer vous dans ce nouveau dossier et lancer CMake sur le répertoire parent:
```cd build-dir ``` puis
```cmake ..```
6. Une fois réalisé, appelez Make sur le répertoire courant
```make```
7. Vous pouvez désormais lancer le jeu:
```./ProjetTowerDefense```




