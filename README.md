# Chronopil

<img alt="Build Status" src="https://img.shields.io/badge/build-passing-brightgreen">

## Description

Chronopil est un dispositif électronique intelligent conçu pour aider les utilisateurs à gérer leurs médicaments de manière simple, sécurisée et automatisée. Ce projet combine des technologies modernes comme les capteurs d'empreintes digitales, les écrans OLED, les électroaimants et les alarmes programmables pour offrir une solution pratique et fiable.

L'objectif principal de Chronopil est de garantir que les utilisateurs prennent leurs médicaments à temps, tout en sécurisant l'accès à la boîte à pilules grâce à un système de reconnaissance d'empreintes digitales.

---

## Fonctionnalités principales

### 1. **Sécurité par empreinte digitale**
- Chronopil utilise un capteur d'empreintes digitales pour s'assurer que seul l'utilisateur autorisé peut accéder à la boîte à pilules.
- Cela garantit que les médicaments ne tombent pas entre de mauvaises mains, comme des enfants ou des personnes non autorisées.

### 2. **Alarmes programmables avec intervalles**
- Vous pouvez programmer des rappels pour prendre vos médicaments à des heures précises.
- Les alarmes peuvent être configurées avec un intervalle (par exemple, tous les 2 jours) et une date limite (par exemple, jusqu'au 31 décembre 2025).
- Une fois l'alarme déclenchée, le système peut afficher un message sur l'écran OLED et déverrouiller la boîte à pilules.

### 3. **Affichage intuitif avec interface utilisateur**
- Un écran OLED intégré affiche des informations importantes comme :
  - L'heure actuelle.
  - Le calendrier (date du jour).
  - La liste des alarmes programmées.
  - Les messages ou instructions pour l'utilisateur.
- Une interface utilisateur simple permet de naviguer dans les menus à l'aide de boutons pour :
  - Programmer des alarmes.
  - Consulter les alarmes existantes.
  - Déverrouiller la boîte à pilules.

### 4. **Mécanisme de verrouillage par électroaimant**
- Un électroaimant contrôle l'ouverture et la fermeture de la boîte à pilules.
- Une fois que l'utilisateur a pris ses médicaments, le système verrouille automatiquement la boîte pour éviter tout accès non autorisé.

### 5. **Détection de présence**
- Un capteur infrarouge détecte si quelqu'un est à proximité de la boîte.
- Cela peut être utilisé pour activer automatiquement l'écran ou pour déclencher une action spécifique.

---

## Comment ça fonctionne ?

### Étape 1 : **Programmation des alarmes**
- Les alarmes peuvent être programmées directement dans le code ou via l'interface utilisateur.
- Chaque alarme est définie par une heure précise (par exemple, 8h30), un intervalle (par exemple, tous les 2 jours) et une date limite (par exemple, jusqu'au 31 décembre 2025).

### Étape 2 : **Vérification de l'utilisateur**
- Lorsque l'utilisateur souhaite accéder à la boîte à pilules, il doit placer son doigt sur le capteur d'empreintes digitales.
- Si l'empreinte est reconnue, la boîte se déverrouille automatiquement.
- Si l'empreinte n'est pas reconnue, l'accès est refusé.

### Étape 3 : **Affichage des informations**
- L'écran OLED affiche des informations utiles, comme :
  - Les alarmes actives.
  - L'heure et la date actuelles.
  - Des messages pour guider l'utilisateur (par exemple, "Prenez vos médicaments").

### Étape 4 : **Déclenchement des alarmes**
- À l'heure programmée, une alarme se déclenche.
- Le système peut afficher un message sur l'écran, jouer un son (si un buzzer est ajouté) et déverrouiller la boîte à pilules.

### Étape 5 : **Fermeture automatique**
- Une fois que l'utilisateur a pris ses médicaments, le système verrouille automatiquement la boîte à pilules grâce à l'électroaimant.

---

## Installation

Pour installer et utiliser Chronopil, suivez ces étapes :

### 1. **Cloner le projet**
Téléchargez le code source depuis le dépôt GitHub :

```bash
git clone https://github.com/Oered-sudo/Chronopil.git
cd Chronopil
```

### 2. **Configurer l'environnement**
Assurez-vous d'avoir installé PlatformIO ou un autre environnement compatible avec Arduino.

### 3. **Compiler et téléverser le code**
Compilez le projet et téléversez-le sur votre carte électronique (par exemple, ESP32) :

```bash
platformio run --target upload
```

---

## Utilisation

### 1. **Allumer le dispositif**
- Connectez la carte électronique à une source d'alimentation.
- L'écran OLED s'allume et affiche l'heure actuelle.

### 2. **Naviguer dans le menu**
- Utilisez les boutons pour naviguer dans le menu :
  - **UP/DOWN** : Déplacer le curseur dans le menu.
  - **RIGHT** : Sélectionner une option.
  - **LEFT** : Revenir au menu principal.

### 3. **Ajouter des alarmes**
- Accédez à l'option "Set Alarm" dans le menu.
- Utilisez les boutons pour définir l'heure, l'intervalle et la date limite.

### 4. **Consulter les alarmes**
- Accédez à l'option "View Alarms" pour afficher la liste des alarmes programmées.

### 5. **Déverrouiller la boîte**
- Accédez à l'option "Unlock Pillbox" ou placez votre doigt sur le capteur d'empreintes digitales.
- Si l'empreinte est reconnue, la boîte se déverrouille automatiquement.

### 6. **Suivre les rappels**
- Lorsque l'alarme se déclenche, prenez vos médicaments comme indiqué sur l'écran.

### 7. **Fermeture automatique**
- Une fois les médicaments pris, la boîte se verrouille automatiquement.

---

## Objectif

Chronopil est conçu pour répondre aux besoins suivants :

- **Personnes âgées** : Aider les personnes âgées à suivre leur traitement médical sans oublier leurs médicaments.
- **Patients chroniques** : Simplifier la gestion des médicaments pour les patients atteints de maladies chroniques.
- **Soignants** : Offrir un outil pratique pour les soignants qui gèrent les médicaments de plusieurs patients.

Ce projet vise à améliorer la qualité de vie des utilisateurs en rendant la prise de médicaments plus simple, sécurisée et automatisée.

---

## Fonctionnalités futures

Voici quelques idées pour améliorer Chronopil dans le futur :

- **Interface utilisateur avancée** : Ajouter un écran tactile ou une application mobile pour programmer les alarmes plus facilement.
- **Notifications** : Envoyer des rappels sur un smartphone ou par e-mail.
- **Stockage des données** : Sauvegarder les alarmes et les empreintes digitales dans une mémoire persistante (EEPROM ou carte SD).
- **Sonnerie** : Ajouter un buzzer pour alerter l'utilisateur lorsque l'alarme se déclenche.

---

## Crédits

Ce projet a été développé par [Oered-sudo](https://github.com/Oered-sudo) et est open-source. Vous êtes libre de contribuer ou de l'utiliser pour vos propres projets.