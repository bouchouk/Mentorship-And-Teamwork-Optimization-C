# 🚀 Optimisation de l’affectation de contributeurs aux projets

## 🎯 Contexte du projet
L’objectif de ce projet est de résoudre un problème d’**affectation de contributeurs aux projets**.  
Chaque contributeur possède des compétences avec un certain niveau, et chaque projet demande des rôles avec des niveaux minimaux.  

### Contraintes principales :
- Un contributeur ne peut travailler que sur un projet à la fois.  
- Les projets ont une **durée**, une **deadline (best before)** et un **score**.  
- Si un projet finit après sa deadline, le score est pénalisé.  
- Les contributeurs peuvent être **mentorés** par d’autres pour acquérir de nouvelles compétences.  

👉 Mon objectif était de maximiser le **score total** en optimisant l’affectation des contributeurs aux projets.

---

## 🧠 Approche méthodologique

### 1. Première idée : Algorithme génétique
Dès le départ, j’ai identifié ce problème comme un **problème d’optimisation**.  
J’ai donc choisi d’explorer une approche basée sur un **algorithme génétique (GA)** :  
- Population de solutions candidates (chromosomes).  
- Application de **mutation** et **croisement (crossover)** pour générer de nouvelles solutions.  
- Évaluation des solutions avec une **fitness function** prenant en compte :  
  - le score des projets terminés,  
  - le respect des délais,  
  - la progression des compétences des contributeurs.  

### 2. Génération de la première population
Construire une bonne première population est crucial pour éviter de me bloquer dans un **optimum local**.  
J’ai donc combiné une **approche greedy** avec du hasard :  
- Trier les projets selon différents critères (**durée, deadline, nombre de rôles, score**)
- Créer 8 ordonnancements de projets à partir de ces tris (directs et inversés).  
- Générer d’autres chromosomes de manière aléatoire pour garder de la diversité.  

Ainsi, la première population contient à la fois des solutions **guidées** et des solutions **aléatoires**.

### 3. Évaluation & sélection
- Chaque chromosome est évalué par la fitness function.  
- Les meilleurs sont conservés pour former la nouvelle génération.  
---

## 🚀 Résultats
- J’ai mis en place une solution hybride combinant :  
  - **Greedy sorting** (pour guider la première population).  
  - **Algorithme génétique** (pour explorer et améliorer les solutions).  
- Le modèle est capable de produire des affectations valides et d’améliorer progressivement le score total.
- 🎓 **classé premier de ma promotion**, ce projet illustre ma capacité à aborder des problèmes complexes d’optimisation

---
