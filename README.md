# FEM-TetraLin

## Description
Ce projet implémente la **Méthode des Éléments Finis (FEM)** sur des **éléments tétraédriques linéaires** en **élasticité linéaire isotrope homogène**. L'objectif est de résoudre des problèmes mécaniques en modélisant le comportement des matériaux sous différentes conditions de charge et de contrainte.

## État d'avancement
Le code est fonctionnel mais nécessite quelques **ajustements** pour améliorer ses performances :
- **Implémentation d'une matrice creuse** avec **Eigen** pour une meilleure gestion mémoire.
- **Utilisation d'un ThreadPool** pour paralléliser les calculs et améliorer l'efficacité.

## Dépendances
Avant de compiler le projet, assurez-vous d'installer les dépendances suivantes :

### 📌 Bibliothèque requise :
- **Gmsh** : Générateur de maillages.
  
### 🔧 Installation sur Ubuntu :
```bash
# Installation de Gmsh et de sa bibliothèque de développement
sudo apt install gmsh libgmsh-dev
````
## Installation et Compilation
Pour cloner et compiler le projet, exécutez les commandes suivantes :

```bash

# Cloner le dépôt
git clone <url_du_repo>
cd <nom_du_dossier>

# Installation des dépendances gmsh
sudo apt install gmsh && apt install libdev-gmsh

# Générer les fichiers de build avec CMake
cmake -B build

# Compiler le projet
cmake --build build
```

## Dépendances
Le projet repose sur les bibliothèques suivantes :
- **Eigen** : pour les opérations matricielles.
- **Gmsh** : pour la lecture des fichiers .msh, mais aussi effectuer le maillage si forme géométrique seuelement.

## Utilisation
Il est nécessaire d'ajouter le fichier .msh dans la racine du projet, sur lequel les calculs seront basés. Un fichier cylinder.msh est déjà disponible pour tester le code.

---

**TODO :**
- [ ] Intégrer **Eigen::SparseMatrix** pour optimiser le stockage et les calculs.
- [ ] Ajouter un **ThreadPool** pour paralléliser certaines parties du code.
- [ ] Compléter la documentation et fournir des exemples d'utilisation.

---

🚀 **Projet en cours d'amélioration – toute suggestion est la bienvenue !**

