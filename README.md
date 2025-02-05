### Ce programme en C++ effectue une **attaque par brute force** pour tenter de **déverrouiller un fichier RAR protégé par mot de passe**, dans un **cadre académique et éthique**. Il est destiné à **l’apprentissage en cybersécurité** et aux **tests de robustesse des mots de passe**, **toute utilisation illégale est strictement interdite**.  

---

### **Fonctionnement**  
1. **Calcul du nombre total de combinaisons** possibles en fonction du jeu de caractères et de la longueur du mot de passe.  
2. **Génération récursive et test des mots de passe**, en exécutant la commande `unrar` pour vérifier chaque tentative.  
3. **Affichage de la progression** et enregistrement du mot de passe trouvé dans un fichier.  
4. **Interaction avec l'utilisateur** pour récupérer :  
   ✅ Le fichier RAR à attaquer  
   ✅ Les caractères autorisés pour le mot de passe  
   ✅ La longueur minimale et maximale  
   ✅ Le fichier de sortie pour enregistrer le mot de passe découvert  

---

### **Requirements (Prérequis)**  
Pour exécuter ce programme correctement, vous devez avoir :  
🔹 **Un système Linux** (ou WSL sous Windows)
🔹 **Installer git**
```bash
$ sudo apt install git
```
🔹 **Le compilateur g++** installé (via `sudo apt install g++` si nécessaire)  
🔹 **L'outil `unrar` installé** (`sudo apt install unrar`)  
🔹 **Des permissions suffisantes** pour exécuter des commandes système  

**Compilation et exécution :**  
```bash
$ g++ -o brute_force_rar brute_force_rar.cpp
$ ./brute_force_rar
```
---
### **Installation :**
---

### **Limitations et améliorations possibles**  
❌ **Utilisation de `system()`** → Risques de sécurité et performances limitées. Une bibliothèque comme **UnRAR SDK** serait plus efficace.  
❌ **Méthode récursive** → Consomme beaucoup de mémoire et ralentit le processus. Une approche itérative serait plus optimisée.  
❌ **Aucune gestion avancée des erreurs** → Si le fichier n’existe pas ou si `unrar` n’est pas installé, le programme pourrait planter.  

---

### **Conclusion**  
Ce programme met en évidence la **vulnérabilité des mots de passe courts et faibles** face aux attaques par brute force. Il doit être utilisé uniquement **dans un cadre d’apprentissage et de tests de sécurité**.  

🔹 **Zujie — Apprendre, comprendre, sécuriser.** 🚀
