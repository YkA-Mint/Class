#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

extern char date[];

// Structures et types
struct Transaction {
    int idEtu;
    float montant;
    char *description;
    struct Transaction *suivant;
};
typedef struct Transaction T_Transaction;

struct Block {
    int idBloc;
    char *dateBloc; // date du bloc sous la forme AAAAMMJJ (ex : 20231009 pour le 09/10/2023)
    T_Transaction *listeTransactions;
    struct Block *suivant;
};
typedef struct Block T_Block;

typedef T_Block *BlockChain;




// Cr�ation et initialisation des structures
T_Transaction *creerTransaction(int id, float montant, char *descr);
T_Block *creerBloc(int id, char* date);


// 1.	Ajout d'une transaction en t�te d'une liste de transactions :
T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction);

// 2.	Ajout d'un bloc en t�te de la BlockChain :
BlockChain ajouterBlock(BlockChain bc);

// 3.	Calcul de la somme des EATCoin cr�dit�s et d�pens�s par un �tudiant sur une journ�e :
float totalTransactionEtudiantBlock(int idEtu, T_Block b);

// 4.	Calcul du solde total d'un �tudiant:
float soldeEtudiant(int idEtu, BlockChain bc);

// 5.	Rechargement du compte d�un �tudiant :
void crediter(int idEtu, float montant, char *descr, BlockChain bc);

// 6.	Paiement d�un repas :
int payer(int idEtu, float montant, char *descr, BlockChain bc);

// 7.	Historique d�un �tudiant :
void consulter(int idEtu, BlockChain bc);

// 8.	Transfert de EATCoins entre deux �tudiants :
int transfert(int idSource, int idDestination, float montant, char *descr, BlockChain bc);





// UTILS
void viderBuffer() ;
char* New_date(char* datechar, int nombre);
void AfficherTransactionsBlock(T_Block);
T_Block* RechercherBlock(char *, T_Block*);
void AfficherTransactionEtudiantBlock(int, T_Block);

void Afficher_Transaction(T_Transaction*);
void Tout_Afficher(BlockChain);
void Tout_Liberer(BlockChain);


#endif // TP3_H_INCLUDED
