
# E_Bank System

Welcome to the E_Bank System, a command-line banking application written in C. This system provides both a simple interface and a complete interface for managing clients and transactions. Created by Ayoub Hammami as a Dev-Class Project Work.

## Features

### Simple Interface

- Modify client information
- Delete a client
- Add a new client
- View all clients
- View all transactions
- Perform a transaction
- View client information

### Complete Interface

#### Admin Interface

- Access with the password "ensi"
- Modify client information
- Delete a client
- Add a new client
- View all clients
- View all transactions
- Return to the user selection page
- Quit the program

#### Client Interface

- Log in with an existing client ID
- Create a new client account
- View client information
- Modify client information
- Perform a transaction
- Delete the client account
- Return to the user selection page
- Quit the program

## Security Measures

For security reasons, the application is designed with a clear separation between the client and admin interfaces. This ensures that:

- **Client Interface:** Clients can only modify or make transactions with their own ID (password). They are restricted to actions related to their individual accounts.

- **Admin Interface:** Admins, identified with a specific password, have broader access to modify or delete any client's information, add new clients, and view all transactions. This separation enhances the security of the application, mimicking real-life banking systems.

## Getting Started

1. Clone the repository to your local machine.
2. Open the project in your preferred C compiler or code editor (e.g., Visual Studio Code).
3. Compile and run the `E_banking Source Code` file or run the executable code directly.
4. Dont forget to download the whole file on your computer so while running the program it updates the files clients and transactions.
5. The transactions file, E_clients file ,the executable code and the source code should all be on the same folder to work correctly.

## Usage

- For the admin interface, use the password "ensi".
- Follow the on-screen prompts to navigate through the interfaces and perform actions.
- Type the date at first so the transactions that occur will be registered with that date (to mimic real banking systems).
- Note that the ID used by a client is unique and cannot be associated with another client.
- You will get to choose between the simple interface for testing all the functions of the program, and the full interface which mimics real-world applications layout(client side and admin side).
- The program interface and outputs are written in French.

## Functions and their utility:
* For more information about how each function works and the algorithms it use, take a look at the source code.

```c
// Function to write the current date for valid transaction dates
date ecrire_date();

// Function to modify a given client's information
void modifier_client(node* head, int targetID);

// Function to delete a client from the linked list
void supprimer_client_linked_list(node** head, int targetID);

// Function to delete a client from the Clients file
void supprimer_client_fichier(int targetID);

// Function to add a dynamically allocated client to the Clients file
void add_client_tofile_from_node(node* new_node);

// Function to dynamically allocate space and create a new client node
void addNode(node** head, client client);

// Function to clear the screen for better user experience
void clear_screen();

// Function to check if the entered ID is valid (8 digits)
int check_id(int id);

// Function to check if the entered ID already exists in the client database
int isCinUnique(node* head, int targetID);

// Function to clear the input buffer
void clear_input_buffer();

// Function to create a new client account
void creer_client(node** head);

// Function to display client information
void afficher_info_client(node* head, int targetID);

// Function to free the memory used by the linked list
void pisslow_memory(node* head);

// Function to perform a transaction
void transaction(node* head, int targetID, date x);

// Function to display all client information (admin only)
void afficher_tout();

// Function to display all transactions with details (admin only)
void afficher_transactions();

// Function to load clients from the file into a linked list
void load_clients(node** head);

// Function to display the admin interface
void interfaceAdmin(node** head, date x);

// Function to display the client interface
void interfaceClient(node** head, date x);

// Main function containing the primary user interface loop
void interfacePrincipale(node** head, date x);

// Function to clear the boolean values
void effacer_bool();

// Function to check if the deleted client is successfully removed from the linked list
int nombre_elements(node* head);

// Function to validate a date
int is_valid_date(int jour, int mois, int annee);

// Function to obtain valid user input for a date
int obtenir_saisie_valide(const char *invite);
``` 


## Contributing

Feel free to contribute to the project by submitting bug reports, feature requests, or code improvements.

## Credits

Developped by: Ayoub Hammami
                        -1st year student at "National School of Computer Science".

## License

This project is licensed under the [MIT License](LICENSE)
