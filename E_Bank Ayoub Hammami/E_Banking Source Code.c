#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct {
    int jour;
    int mois;
    int annee;
} date;

typedef struct {
    int cin;    // 8 digits ID
    char name[12];
    char family_name[12];
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



//Description des fonctions 
int is_valid_date(int jour, int mois, int annee) {
    return (annee > 0 && mois >= 1 && mois <= 12 && jour >= 1 && jour <= 31);
}

int obtenir_saisie_valide(const char *invite) {
    int saisie;

    do {
        printf("%s", invite);
        if (scanf("%d", &saisie) != 1) {
            clear_input_buffer();
            printf("Saisie invalide. Veuillez entrer un nombre.\n");
        } else {
            clear_input_buffer();
            return saisie;
        }
    } while (1);
}

date ecrire_date() {
    date x;

    printf("Veuillez entrer la date d'aujourd'hui pour une experience optimale du programme.\n");
    printf("*************************************************************************************\n\n");
    x.jour = obtenir_saisie_valide("Jour :\n");
    while (!is_valid_date(x.jour, 1, 1)) {
        printf("Veuillez entrer un jour valide.\n");
        x.jour = obtenir_saisie_valide("Jour : ");
    }
    x.mois = obtenir_saisie_valide("Mois :\n");
    while (!is_valid_date(1, x.mois, 1)) {
        printf("Veuillez entrer un mois valide.\n");
        x.mois = obtenir_saisie_valide("Mois : ");
    }
    x.annee = obtenir_saisie_valide("Annee :\n");
    while (!is_valid_date(1, 1, x.annee)) {
        printf("Veuillez entrer une annee valide.\n");
        x.annee = obtenir_saisie_valide("Annee : ");
    }

    return x;
}

void modifier_client(node* head, int targetID) {
    node* current = head;

    while (current != NULL && current->data.cin != targetID) {
        current = current->suiveur;
    }

    if (current != NULL) {
        supprimer_client_fichier(targetID);
        afficher_info_client(head, targetID);
        printf("\n\n");
        printf("Nouvelles informations du client (Re-ecrire les meme champs pour ne pas modifier):\n");

        printf("Nouveau nom: ");
        fgets(current->data.name, sizeof(current->data.name), stdin);
        current->data.name[strcspn(current->data.name, "\n")] = '\0';
        

        printf("Nouveau prenom: ");
        fgets(current->data.family_name, sizeof(current->data.family_name), stdin);
        current->data.family_name[strcspn(current->data.family_name, "\n")] = '\0';

        int target=0;
        while(1) {
        printf("Nouveau numero de carte d'identite nationale:\n");
        scanf("%d", &target);
        clear_input_buffer();
        if ((check_id(target) == 1) && ( target==current->data.cin  || isCinUnique(head,target)==1)){
            current->data.cin = target;
            break;
        }
        else{
            printf("L'ID est deja utilise ou invalide. Veuillez ressayer\n\n");
        }
        }
        
        add_client_tofile_from_node(current);
        clear_screen();
        printf("Les informations du client ont ete mises a jour avec succes.\n");
        afficher_info_client(head, current->data.cin);
    } else {
        printf("Aucun client trouve avec l'ID : %d\n", targetID);
    }
}

void supprimer_client_linked_list(node** head, int targetID) {
    if (isCinUnique(*head, targetID) == 1) {
        printf("Client Introuvable..\n");
        return;
    } else {
        node* current = *head;
        node* previous = NULL;

        while (current != NULL && current->data.cin != targetID) {
            previous = current;
            current = current->suiveur;
        }

        if (current != NULL) {
            if (previous != NULL) {
                previous->suiveur = current->suiveur;
                printf("Le client avec ID: %d -- Nom: %s -- Prenom: %s a ete supprime avec succes!",current->data.cin,current->data.name,current->data.family_name);
                free(current);
            } else {
                printf("Le client avec ID: %d -- Nom: %s -- Prenom: %s a ete supprime avec succes!",current->data.cin,current->data.name,current->data.family_name);
                *head = current->suiveur;
            }
            
        }else {
            printf("Erreur : Le client n'a pas ete trouve\n");
        }
    }
}

void supprimer_client_fichier(int targetID) {
    FILE* file = fopen("Clients E_bank.txt", "r");
    if (file == NULL) {
        printf("Il semble qu'il y a une erreur lors de la lecture du fichier clients..\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Erreur lors de la création du fichier temporaire.\n");
        return;
    }

    char line[255];
    int currentID;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "ID: %d", &currentID) != 1 || currentID != targetID) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("Clients E_bank.txt");
    rename("temp.txt", "Clients E_bank.txt");
}

void add_client_tofile_from_node(node* new_node) {
    FILE* pF = fopen("Clients E_bank.txt", "a");
    if (pF == NULL) {
        printf("Il semble qu'il ya une erreur lors de la lecture de fichier des clients..\n");
        return;
    }

    fprintf(pF, "ID: %d -- Nom: %s -- Prenom: %s -- Balance: %.2f\n",
            new_node->data.cin, new_node->data.name, new_node->data.family_name, new_node->data.balance);
    fclose(pF);
}

void addNode(node** head, client client) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "ERREUR D'ALLOCATION!\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = client;
    new_node->suiveur = *head;
    *head = new_node;
    
}

void clear_screen() {
    system("cls");
}

int check_id(int id) {
    return (id >= 10000000 && id <= 99999999);
}

int isCinUnique(node* head, int targetID) {
    node* current = head;
    while (current != NULL) {
        if (current->data.cin == targetID) {
            return 0;  
        }
        current = current->suiveur;
    }
    return 1; 
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void creer_client(node** head) {
    node* nouveau_node = (node*)malloc(sizeof(node));

    if (nouveau_node == NULL) {
        fprintf(stderr, "ERREUR D'ALLOCATION. LIBERER LA MEMOIRE!\n");
        exit(EXIT_FAILURE);
    }

    printf(">>Donner le nom du client :\n");
    fgets(nouveau_node->data.name, sizeof(nouveau_node->data.name), stdin);
    nouveau_node->data.name[strcspn(nouveau_node->data.name, "\n")] = '\0';
   
    
    printf(">>Donner le prenom du client :\n");
    fgets(nouveau_node->data.family_name, sizeof(nouveau_node->data.family_name), stdin);
    nouveau_node->data.family_name[strcspn(nouveau_node->data.family_name, "\n")] = '\0';

    while (1) {
        printf(">>Donner le numero de carte d'identite nationale :\n");

        if (scanf("%d", &(nouveau_node->data.cin)) == 1) {
            if (check_id(nouveau_node->data.cin) && isCinUnique(*head, nouveau_node->data.cin)) {
                break;
            } else {
               
                printf(">>Numero de carte d'identite nationale invalide ou deja utilise. Veuillez entrer un nouveau numero valide (8 chiffres).\n\n");
            }
        } else {
            printf(">>Entree invalide. Veuillez entrer un numero de carte d'identite nationale valide (8 chiffres).\n");
        }
    }

    nouveau_node->data.balance = 0;
    add_client_tofile_from_node(nouveau_node);
    nouveau_node->suiveur = *head;
    *head = nouveau_node;
    printf("Votre compte a ete cree avec success!!\n\n");
    clear_input_buffer();
}

void afficher_info_client(node* head, int targetID) {
    node* current = head;

    while (current != NULL) {
        if (current->data.cin == targetID) {
            printf(">>Informations du client (ID: %d):\n", targetID);
            printf("---------------------------------------\n");
            
            printf(">>Nom: %s\n", current->data.name);
            printf("---------------------------------------\n");
          
            printf(">>Prenom: %s\n", current->data.family_name);
            printf("---------------------------------------\n");
           
            printf(">>Numero de carte d'identite nationale: %d\n", current->data.cin);
            printf("---------------------------------------\n");
            printf(">>Solde: %.2f\n", current->data.balance);
            printf("---------------------------------------\n");
            return;
        }
        current = current->suiveur;
    }

    printf(">>Aucun client trouve avec l'ID : %d\n", targetID);
}

void pisslow_memory(node* head) {
    while (head != NULL) {
        node* next = head->suiveur;
        free(head);
        head = next;
    }
}

void transaction(node* head,int targetID, date x) {
    FILE* pF = fopen("transactions.txt", "a");
    if (pF == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    node* current = head;
    while (current != NULL) {
        if (current->data.cin == targetID) {
            float amount;
            printf("Choisissez le type de transaction:\n");
            printf("*************************************\n");
            printf(" 1.Retirer de l'argent\n");
            printf(" 2.Faire un depot\n");
            printf("--------------------------------------\n");
            printf("Votre choix (1 ou 2): ");

            int choice;
            scanf("%d", &choice);
            clear_input_buffer();

            switch (choice) {
                case 1:
                    printf("Montant à retirer : ");
                    scanf("%f", &amount);
                    clear_input_buffer();

                    if (amount > 0 && amount <= current->data.balance) {
                        current->data.balance -= amount;
                        supprimer_client_fichier(current->data.cin);
                        add_client_tofile_from_node(current);
                        printf("Retrait reussi. Nouveau solde : %.2f\n", current->data.balance);
                        fprintf(pF, "ID: %d, Type: %s, Montant: %.2f, Nouveau Solde: %.2f, Date: Le %d/%d/%d \n",
                                current->data.cin, "Retrait", amount, current->data.balance, x.jour, x.mois, x.annee);
                    } else {
                        printf("Montant invalide ou solde insuffisant.\n");
                    }
                    break;

                case 2:
                    printf("Montant a deposer : ");
                    scanf("%f", &amount);
                    clear_input_buffer();

                    if (amount > 0) {
                        current->data.balance += amount;
                        supprimer_client_fichier(current->data.cin);
                        add_client_tofile_from_node(current);
                        printf("Depot reussi. Nouveau solde : %.2f\n", current->data.balance);
                        fprintf(pF, "ID: %d, Type: %s, Montant: %.2f, Nouveau Solde: %.2f, Date: Le %d/%d/%d \n",
                                current->data.cin, "Depot", amount, current->data.balance, x.jour, x.mois, x.annee);
                    } else {
                        printf("Montant invalide.\n");
                    }
                    break;

                default:
                    printf("Choix invalide.\n");
            }

            fclose(pF);
            return;
        }

        current = current->suiveur;
    }

    printf("Aucun client trouvé avec l'ID : %d\n", targetID);
    fclose(pF);
}

void afficher_tout() {
    FILE* pF = fopen("Clients E_bank.txt", "r");
    if (pF == NULL) {
        printf("Il semble qu'il ya une erreur lors de la lecture de fichier des clients. Fichier introuvable\n");
        return;
    }
    char line[255];
    printf(">>Affichage des clients en cours..\n");
    while (fgets(line, sizeof(line), pF) != NULL) {
        printf("%s\n", line);
        printf("--------------------------------------------------------\n");
    }
    fclose(pF);
}

void afficher_transactions() {
    FILE* pF = fopen("transactions.txt", "r");
    if (pF == NULL) {
        printf("Il semble qu'il ya une erreur lors de la lecture de fichier des transactions. Fichier introuvable\n");
        return;
    }
    char line[255];
    printf(">>Affichage des transactions en cours..\n");
    while (fgets(line, sizeof(line), pF) != NULL) {
        printf("%s\n", line);
        printf("--------------------------------------------------------\n");
    }
    fclose(pF);
    clear_input_buffer();
}

void load_clients(node** head) {
    FILE* pF = fopen("Clients E_bank.txt", "r");
    if (pF == NULL) {
        printf("Il semble qu'il ya une erreur lors de la lecture de fichier des clients..\n");
        return;
    }
    client client;
    while (fscanf(pF, "ID: %d -- Nom: %16s -- Prenom: %16s -- Balance: %f\n", 
                  &client.cin, client.name, client.family_name, &client.balance) == 4) {
        addNode(head, client);
    }
    fclose(pF);
}

void interfaceClient(node** head,date x) {
    int choice;
    int idClient;
    int choice2;
    
    printf("\nInterface Client :\n");
    printf("1. Creer un compte\n");
    printf("2. Se connecter\n");
    printf("3. Retourner a la page precedente\n");
    printf("4. Quitter\n");
    printf("***********************************\n");

    printf("Entrez votre choix : \n\n");
    scanf("%d", &choice);
    clear_input_buffer();

    switch (choice) {
        case 1:
            clear_screen();
            creer_client(head);
            effacer_bool();
            printf("\n");
            break;
        case 2:
            clear_screen();
            printf("Entrez votre ID client : ");
            scanf("%d", &idClient);
            clear_input_buffer();
            if (isCinUnique(*head,idClient)==1){
                printf("Utilisateur non trouvé..\n");
                printf("Voulez vous creer un compte?\n");
                printf("1. Oui");
                printf("2. Non");
                scanf("%d",&choice2);
                clear_input_buffer();
                if(choice2 == 1){
                    creer_client(head);
                    effacer_bool();
                    break;
                }
                else if (choice2==2){
                    printf("Merci pour votre visite!\n");
                    clear_screen();
                    return;
                }
            }
            else{
                int choice3;
                node* current = *head;
                while (current != NULL) {
                if (current->data.cin == idClient);{
                    printf("Bienvenue %s\n",current->data.name);
                    break;}
                current = current->suiveur;
                }
                free(current);
                printf("1. Consulter les informations de votre compte.\n");
                printf("2. Modifier les informations de votre compte\n");
                printf("3. Transaction bancaire.\n");
                printf("4. Supprimer votre compte\n");
                printf("5. Retour au page precedente\n");
                printf("6. Quitter.\n");
                scanf("%d",&choice3);
                clear_input_buffer();
                printf("Votre choix est %d\n",choice3);
                switch (choice3)
                {
                case 1:
                    clear_screen();
                    afficher_info_client(*head,idClient);
                    printf("\n\n");
                    effacer_bool();
                    break;
                case 2:
                    clear_screen();
                    modifier_client(*head,idClient);
                    printf("\n\n");
                    effacer_bool();
                    break;
                case 3:
                    clear_screen();
                    transaction(*head,idClient,x);
                    printf("\n\n");
                    effacer_bool();
                    break;
                case 4:
                    clear_screen();
                    supprimer_client_fichier(idClient);
                    supprimer_client_linked_list(head,idClient); 
                    effacer_bool();
                    break;
                case 5:
                    clear_screen();
                    printf("Retour en cours..\n");
                    effacer_bool();
                    return;
                case 6:
                    printf("Fermeture en cours..\n");
                    pisslow_memory(*head);
                    exit(0);        
                default:
                    printf("Choix invalide..\n");
                    printf("\n\n");
                    effacer_bool();
                    break;
                }
            }
            break;

        case 3:
            printf("Fermeture de l'Interface Client...\n");
            return;
        case 4:
           printf("Fermeture en cours..\n");
           pisslow_memory(*head);
           exit(0);
        default:
            printf("Choix invalide. Réessayez.\n");
    }
}

void interfaceAdmin(node** head,date x) {
    int choix;
    int hh;
    while (1) {
        printf("\nInterface Administrateur :\n");
        printf("1. Modifier Client\n");
        printf("2. Supprimer Client\n");
        printf("3. Ajouter Client\n");
        printf("4. Afficher Tous les Clients\n");
        printf("5. Afficher transactions\n");
        printf("6. Retourner a la selection Admin/Client\n");
        printf("7. Quitter tout le programme\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        clear_input_buffer();

        switch (choix) {
            case 1:
                clear_screen();
                printf("Saisir l'ID du client que vous souhaitez modifer:\n");
                scanf("%d",&hh);
                modifier_client(*head,hh);
                effacer_bool();
                break;
            case 2:
                clear_screen();
                printf("Saisir l'ID du client que vous souhaitez supprimer:\n");
                scanf("%d",&hh);
                supprimer_client_fichier(hh);
                supprimer_client_linked_list(head,hh);
                effacer_bool();
                break;
            case 3:
                clear_screen();
                creer_client(head);
                printf("\n\n");
                effacer_bool();
                break;
            case 4:
                clear_screen();
                afficher_tout();
                printf("\n\n");
                effacer_bool();
                break;
            case 7:
                printf("Fermeture de l'Interface Administrateur...\n");
                printf("*******************************************\n\n");
                effacer_bool();
                pisslow_memory(*head);
                exit(0);
            case 5 :
                 clear_screen();
                 afficher_transactions();
                 printf("\n\n");
                 effacer_bool();
                 break;
            case 6:
                effacer_bool();
                return;  
            default:
                printf("Choix invalide. Réessayez.\n\n");
                printf("\n\n");
                effacer_bool();
        }
    }
}

void interfacePrincipale(node** head,date x) {
    int typeUtilisateur;
        printf(">>Bienvenue Au Menu Principale<<\n");
        
        printf("*************************\n");
        printf("1. Administrateur\n");
        printf("2. Client\n");
        printf("3. Quitter\n");
        printf("*************************\n\n");
        printf("Entrez votre choix :");
        scanf("%d", &typeUtilisateur);
        clear_input_buffer();
        clear_screen();
        switch (typeUtilisateur) {
            case 1:
                char password[4];
                printf("Bienvenue a l'espace administrateur\n\n");
                printf("************************************************************\n");
                printf("Ecrire le mot de passe pour acceder a l'espace administrateur:\n");
                printf(">>");
                scanf("%s",&password);
                
                if (strcmp(password, "ensi") == 0){
                    clear_input_buffer();
                    clear_screen();
                    printf("Bienvenu..\n");
                    interfaceAdmin(head,x);
                    break;
                }
                else{
                    printf("\n");
                    printf("Mot de passe incorrecte\n\n");
                    break;}
            case 2:
                interfaceClient(head,x);
                break;

            case 3:
                printf("\n");
                printf("Fermeture de l'Interface Principale...\n");
                pisslow_memory(*head);
                exit(0);
                break;
            default:
                printf("\n"); 
                printf("Choix invalide. Reessayez.\n\n");
        }
    }

int nombre_elements(node* head) {
    int count = 0;
    node* current = head;

    while (current != NULL ) {
        
        count++;
        current = current->suiveur;
    
    }

    return count;
}  

void effacer_bool(){
    int a;
    printf("Vous allez retourner au menu principale. Voulez vous effacer l'ecran?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    scanf("%d",&a);
    if (a==1){
        clear_screen();
    }
}

void interface_classique(node** head,date x){
        int choix;
        printf("1. Modifier Client\n");
        printf("2. Supprimer Client\n");
        printf("3. Ajouter Client\n");
        printf("4. Afficher Tous les Clients\n");
        printf("5. Afficher transactions\n");
        printf("6. Faire une transaction\n");
        printf("7. Afficher les informations d'un client\n");
        printf("8. Quitter tout le programme\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        clear_input_buffer();
        clear_screen();
        switch (choix)
        {
        case 1:
            int ID;
            printf("Ecrire l'ID du client:\n");
            scanf("%d",&ID);
            clear_input_buffer();
            modifier_client(*head,ID);
            effacer_bool();
            
            break;
        case 2:
            int id;
            printf("Ecrire l'ID du client:\n");
            scanf("%d",&id);
            clear_input_buffer();
            supprimer_client_linked_list(head,id);
            supprimer_client_fichier(id);
            break;
        case 3:
            creer_client(head);
            effacer_bool();
            break;    
        case 4 :
            afficher_tout();
            effacer_bool();
            break;
        case 5 : 
            afficher_transactions();
            effacer_bool();
            break;
        case 6: 
            int id1;
            printf("Ecrire l'ID du Client:\n");
            scanf("%d",&id1);
            transaction(*head,id1,x);
            effacer_bool();
            break;
        case 7: 
            int id3;
            printf("Ecrire l'ID du client:\n");
            scanf("%d",&id3);
            afficher_info_client(*head,id3);    
            effacer_bool();
            break;
        case 8: 
            pisslow_memory(*head);
            exit(0);    
            break;
        default:
            printf("Valeur invalide..\n");
            break;
        }
}
int main() {

    int choix;
    node* head;
    head = NULL;
    load_clients(&head);
    int u = nombre_elements(head);
    printf("%d",u);
    date x = ecrire_date();
    clear_screen();
    printf("Voulez vous utiliser la version simple du programme ou la version complete?\n");
    printf("1. Version Simple\n");
    printf("2. Version Complete\n");
    scanf("%d",&choix);
    if( choix == 1 ){
        clear_screen();
        while(1){
            interface_classique(&head,x);
        }
    }
    else if (choix == 2){
        clear_screen();
        while (1){
            interfacePrincipale(&head,x);
        }
    }
    clear_screen();
    
    pisslow_memory(head);
    return 0;
}
