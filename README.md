
# SecretMessage

## Présentation du projet

**SecretMessage** est un programme développé en C++ permettant de cacher et de récupérer un message dans une image au format BMP.

Ce projet utilise la **stéganographie**, une technique qui consiste à dissimuler des informations dans un fichier, ainsi qu'une transformation XOR utilisant une clé.

Le programme fonctionne depuis un terminal et propose deux commandes principales :

- **Encode** : cacher un message dans une image BMP et créer une nouvelle image.
- **Decode** : récupérer et afficher le message caché dans une image BMP.

---

## Fonctionnement

### Encodage

Lors de l'encodage, le programme :

1. Récupère les arguments fournis dans la ligne de commande.
2. Ouvre l'image BMP sélectionnée.
3. Transforme le message à l'aide de la clé XOR.
4. Insère les informations du message dans l'image.
5. Enregistre une nouvelle image contenant le message caché.

### Décodage

Lors du décodage, le programme :

1. Récupère le chemin de l'image encodée et la clé.
2. Ouvre l'image BMP.
3. Extrait les informations du message caché.
4. Utilise la clé XOR pour retrouver le message original.
5. Affiche le message dans la console.

---


## Utilisation

Le programme s'utilise depuis un terminal Windows, notamment PowerShell.

### Préparation du terminal

Avant d'exécuter le programme, il est recommandé de se placer dans le dossier du projet.

```powershell
cd "C:\Chemin\Vers\SecretMessage"
```

Cette commande modifie le **Working Directory**, c'est-à-dire le répertoire de travail du terminal.


### Chemin de l'exécutable

Dans les exemples suivants, `.\SecretMessage.exe` représente le chemin vers le fichier exécutable.

- `.\` désigne le répertoire courant.
- `SecretMessage.exe` est le nom du programme compilé.

Si l'exécutable se trouve dans un sous-dossier, il faut préciser son chemin.

Par exemple :

```powershell
.\x64\Debug\SecretMessage.exe help
```

Il est également possible d'utiliser un chemin absolu :

```powershell
C:\Chemin\Vers\SecretMessage.exe help
```

### Encoder un message

**Syntaxe :**

```powershell
.\SecretMessage.exe encode "image.bmp" "key" "message" "output"
```
> "Image.bmp" est le nom de l'image et le type doit être bmp

> Il est possible de le ranger l'image modifer dans un sous dossier "DossierImage\output" ou autre part "C:\Chemin\Vers\DossierImage\ImageModifier"

**Exemple :**

```powershell
.\SecretMessage.exe encode "image.bmp" "azE 35" "Hello World" "encoded"
```

Cette commande crée une nouvelle image contenant le message caché.

### Décoder un message

**Syntaxe :**

```powershell
.\SecretMessage.exe decode "encoded.bmp" "key"
```

**Exemple :**

```powershell
.\SecretMessage.exe decode "encoded.bmp" "MyKey"
```

**Résultat attendu :**

```text
Decoded message: Hello World
```

## Organisation du projet

| Module | Fonction |
|---|---|
| `CommandLine` | Gestion des arguments, des commandes et de l'affichage |
| `XOR` | Transformation du message avec une clé |
| `Image` | Lecture, modification et écriture des images BMP |

---

##  Difficulté majeure rencontrée

### Problème de lecture du message

Lors du développement, la fonction `ReadMessage` continuait à lire les données de l'image après la fin du message.

Cela provoquait l'affichage de centaines de caractères indésirables après le message original.

### Solution

Nous avons décidé d'enregistrer également la **taille du message dans l'image**.

Lors du décodage, le programme récupère cette information afin de connaître exactement le nombre de caractères à lire.

Cette modification permet d'arrêter la lecture à la fin du message.

---

## Tests et vérifications

Nous avons effectué différents tests afin de vérifier le fonctionnement du programme et sa gestion des erreurs.

### Répertoire de travail et commandes

| Test | Résultat attendu | Résultat obtenu |
|---|---|---|
| Répertoire de travail correct | Programme fonctionnel | Programme fonctionnel |
| Répertoire de travail incorrect | Échec | Message d'erreur de PowerShell :  Le terme «...» n'est pas reconnu comme nom d'applet de commande, fonction, fichier de script ou programme exécutable |
| Répertoire de travail non précisé | Échec | Message d'erreur de PowerShell :  Le terme «...» n'est pas reconnu comme nom d'applet de commande, fonction, fichier de script ou programme exécutable |
| Commande `encode` | Création d'une image contenant le message | Conforme |
| Commande `decode` | Lecture du message caché | Conforme |
| Commande inconnue | Message d'erreur | `Unknown command` |
| Aucune commande | Message d'erreur | `Unknown command` |

### Gestion des images BMP

| Test | Résultat attendu | Résultat obtenu |
|---|---|---|
| Chemin d'image correct | Lecture de l'image | Conforme |
| Chemin d'image incorrect | Message d'erreur | `Failed to open file` |
| Fichier non BMP | Message d'erreur | `Signature invalide : ce fichier n'est pas un BMP ('BM').` |
| Image inférieure à 54 octets | Message d'erreur | `Fichier trop petit pour contenir un en-tete BMP valide.` |

### Gestion des clés et des messages

| Test | Résultat attendu | Résultat obtenu |
|---|---|---|
| Clé valide à l'encodage | Transformation du message | Conforme |
| Clé absente à l'encodage | Message d'erreur | `Key is empty` |
| Clé correcte au décodage | Message original | Conforme |
| Clé incorrecte au décodage | Message illisible | Message illisible |
| Message valide | Création de l'image encodée | Conforme |
| Message vide | Message d'erreur | `Message is empty` |
| Message trop long pour l'image | Message d'erreur | `Message is too long` |

### Gestion de l'image de sortie

| Test | Résultat attendu | Résultat obtenu |
|---|---|---|
| Chemin de sortie correct | Image créée à l'emplacement demandé | Conforme |
| Chemin de sortie incorrect | Création dans le répertoire de travail avec le nom `output.bmp` | Comportement observé |

---

## Répartition du travail

Ce projet a été réalisé en binôme.

| Développeur | Modules réalisés | Responsabilités |
|---|---|---|
| **Louis** | `CommandLine`, `XOR` | Gestion des commandes, des arguments et de la transformation XOR |
| **Hugo** | `Image` | Lecture, modification et sauvegarde des images BMP |

Cette répartition nous a permis de développer séparément les différents modules du programme.

---
