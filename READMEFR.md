# Système E_Bank

Bienvenue dans le système E_Bank, une application bancaire en ligne de commande écrite en C. Ce système offre à la fois une interface simple et une interface complète pour gérer les clients et les transactions. Créé par Ayoub Hammami dans le cadre d'un projet de classe de développement.

## Fonctionnalités

### Interface Simple

- Modifier les informations du client
- Supprimer un client
- Ajouter un nouveau client
- Voir tous les clients
- Voir toutes les transactions
- Effectuer une transaction
- Voir les informations du client

### Interface Complète

#### Interface Admin

- Accès avec le mot de passe "ensi"
- Modifier les informations du client
- Supprimer un client
- Ajouter un nouveau client
- Voir tous les clients
- Voir toutes les transactions
- Retourner à la page de sélection de l'utilisateur
- Quitter le programme

#### Interface Client

- Se connecter avec un identifiant client existant
- Créer un nouveau compte client
- Voir les informations du client
- Modifier les informations du client
- Effectuer une transaction
- Supprimer le compte client

## Sécurité

Pour des raisons de sécurité, l'application est conçue avec une séparation claire entre les interfaces client et admin. Cela garantit que :

- **Interface Client :** Les clients peuvent uniquement modifier ou effectuer des transactions avec leur propre identifiant (mot de passe). Ils sont limités aux actions liées à leurs comptes individuels.

- **Interface Admin :** Les administrateurs, identifiés avec un mot de passe spécifique, ont un accès plus large pour modifier ou supprimer les informations de n'importe quel client, ajouter de nouveaux clients et voir toutes les transactions.

## Pour Commencer

1. Clonez le référentiel sur votre machine locale.
2. Ouvrez le projet dans votre compilateur C préféré ou éditeur de code (par exemple, Visual Studio Code).
3. Compilez et exécutez le fichier `E_banking Source Code` ou exécutez directement le code exécutable.
4. N'oubliez pas de télécharger l'ensemble du fichier sur votre ordinateur afin que, lors de l'exécution du programme, les fichiers clients et transactions soient mis à jour.
5. Les fichiers de transactions, E_clients, le code exécutable et le code source doivent tous être dans le même dossier pour fonctionner correctement.

## Utilisation

- Pour l'interface admin, utilisez le mot de passe "ensi".
- Suivez les invites à l'écran pour naviguer à travers les interfaces et effectuer des actions.
- Tapez la date au début pour que les transactions enregistrées aient cette date (pour imiter les systèmes bancaires réels).
- Notez que l'identifiant utilisé par un client est unique et ne peut pas être associé à un autre client.
- Vous pourrez choisir entre l'interface simple pour tester toutes les fonctions du programme et l'interface complète qui imite la disposition des applications du monde réel (côté client et côté admin).
- L'interface du programme et les sorties sont rédigées en français.

## Fonctions et leur utilité
* Pour plus d'informations sur le fonctionnement de chaque fonction et les algorithmes utilisés, consultez le code source.
```c
// Structures
typedef struct {
    int jour;
    int mois;
    int annee;
} date;

typedef struct {
    int cin;    // 8 digits ID
    char name[18];
    char family_name[18];
    float balance;
} client;

typedef struct node {
    client data;
    struct node* suiveur;
} node;


date ecrire_date(); // Ecriture valide de la date d'aujourd'hui pour afin d'obtenir des transactions avec des dates valides

void modifier_client(node* head, int targetID);// Fonction pour modifier un client donné (l'administrateur a le droit de modifier tout les clients dans le fichier client tandis que un client peut just modifier ses informations (une implementation d'un simple protocole de securité))

void supprimer_client_linked_list(node** head, int targetID);// Fonction pour supprimer un client de la liste chainé

void supprimer_client_fichier(int targetID);// Fonction pour supprimer le client du fichier Clients

void add_client_tofile_from_node(node* new_node);// Une fonction qui peut ajouter un client alloué dynamiquement dans le fichier

void addNode(node** head, client client);// Une fonction qui peut allouer dynamiquement un espace pour creer un client

void clear_screen();// Une fonction pour effacer l'ecran afin d'avoir une experience optimale et renforcer la lisibilité de l'interface.

int check_id(int id);//Une fonction qui verifie si l'ID saisie est valide ou pas (8 digit)

int isCinUnique(node* head, int targetID);// Une fonction qui verifie si l'ID saisie existe deja dans la base de données des clients ou pas pour eliminer les redondances des clients

void clear_input_buffer();// Une fonction pour vider le tampon de lecture pour eviter le "Buffer overflow" qui cause souvant un comportement inpredictible du programme

void creer_client(node** head);// Une fonction qui alloue dynamiquement de l'espace pour un client et l'ajoute au sommet de la liste chainé apres avoir verifier tout les criteres pour creer un compte

void afficher_info_client(node* head, int targetID);//Une fonction qui permet d'afficher les donnees personnelles d'un client (l'admin peut afficher n'importe quel client tandis que un client peut juste afficher ses données seulement)

void pisslow_memory(node* head);// Une fonction qui permet de vider la liste chainé utilisé lors de tout le programme

void transaction(node* head,int targetID, date x);// Une fonction qui permet d'effectuer une transaction (seuelement un client peut effectuer une transaction)

void afficher_tout();// Une fonction qui permet d'effectuer tout les informations des clients (seuelement pour l'admin)

void afficher_transactions();// Une fonction qui permet d'afficher toutes les transactions avec details (seuelemnt pour l'admin)

void load_clients(node** head);// Une fonction qui permet de faire une mise a jour (Permet d'ajouter tout les clients dans le fichier dans une liste chaine au debut du programme pour une manipulation plus facile)

void interfaceAdmin(node** head,date x);//Une fonction qui permet d'afficher les fonctions et les services disponibles pour l'admin (Le mot de passe est "ensi" vous pouvez le changer au cas de besoin)

void interfaceClient(node** head,date x);// Une fonction qui permet d'afficher les fonctions et les services disponibles pour le client(un client peut connecter a son compte existant a l'aide d'un mot de passe qui est son ID ou il cree un compte)

void interfacePrincipale(node** head,date x); // Une fonction qui est en boucle infini lors de l'execution du programme qui regroupe tout les fonctions et qui donne le choix au debut si l'utilisateur est un client ou admin

void effacer_bool();// Une fonction qui demande de l'utilisateur si il veut effacer l'ecran 

int nombre_elements(node* head);// Une fonction utilisé pour verifier si le client supprimé de la liste chainé est supprimé avec succes ou non, permet aussi de verifier si load_clients fonctionne correctement

int is_valid_date(int jour, int mois, int annee);// Une fonction qui est utilisé pour saisir une date valide

int obtenir_saisie_valide(const char *invite);// Une fonction qui est utilisé pour saisir une date valide
```
## À Propos de l'Auteur

Ce projet a été réalisé par Ayoub Hammami , un etudiant en 1ere année a L'ecole nationale de sciences de l'informatique,dans le cadre d'un travail de classe en développement. Je suis ouvert aux commentaires, suggestions d'amélioration, signalements de bugs, et contributions de la communauté.

N'hésitez pas à ouvrir des issues pour discuter de nouvelles fonctionnalités, signaler des problèmes, ou simplement partager vos idées. Les contributions sous forme de pull requests sont également les bienvenues.

## Contact

- Nom: Ayoub Hammami
- Email: issaayoubyoru@gmail.com
- LinkedIn: https://linkedin.com/in/ayoub-hammami
