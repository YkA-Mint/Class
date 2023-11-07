#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

char date[] = "07112023";

/* ********************************
 * Cr�ation et initialisation Bloc
 ******************************** */
T_Block *creerBloc(int id, char* date){
    T_Block *nouveauBloc = malloc(sizeof(T_Block));
    if (nouveauBloc != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauBloc->dateBloc = malloc(strlen(date) + 1);
        strcpy(nouveauBloc->dateBloc,date);
        nouveauBloc->idBloc = id;
        nouveauBloc->listeTransactions = NULL;
        nouveauBloc->suivant = NULL;
    }

    return nouveauBloc;
}

/* **************************************
 * Cr�ation et initialisation Transaction
 ************************************** */
T_Transaction *creerTransaction(int id, float montant, char *descr) {
    T_Transaction *nouvelleTransaction = malloc(sizeof(T_Transaction));
    if (nouvelleTransaction != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouvelleTransaction->description = malloc(strlen(descr) + 1); // Important : malloc permet d'avoir l'espace m�moire d�di� pour notre champ de structure
        strcpy(nouvelleTransaction->description,descr);
        nouvelleTransaction->idEtu = id;
        nouvelleTransaction->montant = montant;
        nouvelleTransaction->suivant = NULL;
    }

    return nouvelleTransaction;
}

/* ********************************
 * 1.	Ajout d'une transaction en t�te d'une liste de transactions :
 ******************************** */
T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction) {
    T_Transaction *nouvelleTransaction = creerTransaction(idEtu,montant,descr);
    if(listeTransaction!=NULL){
        nouvelleTransaction->suivant = listeTransaction;
        listeTransaction = nouvelleTransaction;
    }
    else{
        listeTransaction = nouvelleTransaction;
    };
    return listeTransaction;
}



/* ********************************
 * 2.	Ajout d'un bloc en t�te de la BlockChain :
 ******************************** */
BlockChain ajouterBlock(BlockChain bc){
    if(bc==NULL){
        T_Block *nouveauBlock = creerBloc(0,date);
        bc = nouveauBlock;
    }
    else{
        T_Block *nouveauBlock = creerBloc((bc->idBloc)+1,date);
        nouveauBlock->suivant = bc;
        bc = nouveauBlock;
    }
    return bc;
}


/* ********************************
 * 3.	Calcul de la somme des EATCoin cr�dit�s et d�pens�s par un �tudiant sur une journ�e :
 ******************************** */
float totalTransactionEtudiantBlock(int idEtu, T_Block b){
    float somme=0;
    T_Transaction *TransactionCurrent =b.listeTransactions;
    while(TransactionCurrent!=NULL){
        if(TransactionCurrent->idEtu==idEtu) {
            somme += TransactionCurrent->montant;
        }
        TransactionCurrent=TransactionCurrent->suivant;
    }
    return somme;
}


/* ********************************
 * 4.	Calcul du solde total d'un �tudiant:
 ******************************** */
float soldeEtudiant(int idEtu, BlockChain bc){
    float solde=0;
    T_Block *Block_current = bc;
    while(Block_current!=NULL){
        solde += totalTransactionEtudiantBlock(idEtu,*Block_current);
        Block_current = Block_current->suivant;
    }
    return solde;
}


/* ********************************
 * 5.	Rechargement du compte d�un �tudiant :
 ******************************** */
void crediter(int idEtu, float montant, char *descr, BlockChain bc){
    bc->listeTransactions = ajouterTransaction(idEtu, montant, descr, bc->listeTransactions);
    printf("Compte correctement credite\n");
    printf("Recharge %f\n", montant);
}


/* ********************************
 * 6.	Paiement d'un repas :
 ******************************** */
int payer(int idEtu, float montant, char *descr, BlockChain bc){
    if(soldeEtudiant(idEtu,bc)>=montant){
        bc->listeTransactions = ajouterTransaction(idEtu,-montant,descr,bc->listeTransactions);
        printf("compte cprrecttement debite");
        return 1;
    }
    else {
        printf("il n'y a pas assez d'argent");
        return 0;
    }
}


/* ********************************
 * 7.	Historique d�un �tudiant :
 ******************************** */
void consulter(int idEtu, BlockChain bc) {
    printf("Solde de l'etudiant : %.2f EATCoin \n", soldeEtudiant(idEtu, bc));
    printf("Les 5 derni�res transactions:\n");
    int count = 0;
    T_Block *b = bc;
    while (b != NULL && count < 5) {
        printf("\n|\n|\n| ###########-bloc-n%d--(%s)-######  ###    ##      #\n| #",b->idBloc,b->dateBloc);
        T_Transaction *t =b->listeTransactions;
        while (t != NULL  && count < 5) {
            if (t->idEtu == idEtu) {
                Afficher_Transaction(t);
                count++;
            }
            t=t->suivant;
        }
        b = b->suivant;
    }
}


/* ********************************
 * 8.	Transfert de EATCoins entre deux �tudiants :
 ******************************** */
int transfert(int idSource, int idDestination, float montant, char *descr, BlockChain bc){
    float SoldeSource = soldeEtudiant(idSource,bc);
    if(SoldeSource >= montant){
        bc->listeTransactions = ajouterTransaction(idSource,-montant,descr,bc->listeTransactions);
        bc->listeTransactions = ajouterTransaction(idDestination,montant,descr,bc->listeTransactions);
        return 1;
    }
    else{
        return 0;
    }
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

T_Block* RechercherBlock(char* dateBloc, T_Block* bc){
    T_Block* Add_block=NULL;
    T_Block* Block_actuel = bc;
    while(Block_actuel!=NULL && Add_block==NULL){
        if(!strcmp(Block_actuel->dateBloc,dateBloc))
            Add_block=Block_actuel;
        Block_actuel = Block_actuel->suivant;
    }
    return Add_block;
}
void AfficherTransactionsBlock(T_Block b){
    T_Transaction *TransactionActuelle = b.listeTransactions;
    printf("\n|\n|\n| ###########-bloc-n%d--(%s)-######  ###    ##      #\n| #",b.idBloc,b.dateBloc);
    while(TransactionActuelle!=NULL){ // On parcours toutes les transactions du bloc
        Afficher_Transaction(TransactionActuelle);
        TransactionActuelle = TransactionActuelle->suivant;
    }
    printf("\n| #########\n|");
}
/* MENU 3 */
void AfficherTransactionEtudiantBlock(int idEtu, T_Block b){
    int id_exist = 0;
    T_Transaction *TransactionActuelle = b.listeTransactions;
    while(TransactionActuelle!=NULL){ // On parcours toutes les transactions du bloc
        if (TransactionActuelle->idEtu == idEtu)
        {
            Afficher_Transaction(TransactionActuelle);
            id_exist = 1;
        }
        TransactionActuelle = TransactionActuelle->suivant;
    }
    if (id_exist == 0)
    {
        printf("idetu n'est pas exist le transaction dans ce datebloc");
    }
}
/* Fonction bonus */
void Afficher_Transaction(T_Transaction* t){ // Affichage d'une transaction
    printf("\n| #    ###--------------------###");
    printf("\n| #            IDetu : %d",t->idEtu);
    printf("\n| #          Montant : %f",t->montant);
    printf("\n| #      Description : %s",t->description);
    printf("\n| #    ###--------------------###\n| #");
}
void Tout_Afficher(BlockChain bc){ // Affichage des toutes les transactions avec les blocs : blokchain complete
    T_Block *Block_actuel = bc;
    while(Block_actuel!=NULL){
        printf("|\n|\n| ###########-bloc-n%d--(%s)-######  ###    ##      #\n| #",Block_actuel->idBloc,Block_actuel->dateBloc);
        T_Transaction *TransactionActuelle = Block_actuel->listeTransactions;
        while(TransactionActuelle!=NULL){
            Afficher_Transaction(TransactionActuelle);
            TransactionActuelle = TransactionActuelle->suivant;
        }
        printf("\n| #########\n|");
        Block_actuel = Block_actuel->suivant;
    }
}
void Tout_Liberer(BlockChain bc){
    T_Block *Block_actuel = bc;
    T_Block *Block_Prochain = bc;
    T_Transaction *TransactionActuelle = Block_actuel->listeTransactions;
    T_Transaction *TransactionProchaine = Block_actuel->listeTransactions;
    while(Block_Prochain!=NULL){
        Block_actuel=Block_Prochain;
        T_Transaction *TransactionActuelle = Block_actuel->listeTransactions;
        while(TransactionProchaine!=NULL){
            TransactionActuelle = TransactionProchaine;
            TransactionProchaine = TransactionActuelle->suivant;
            free(TransactionActuelle->description);
            free(TransactionActuelle);
        }
        Block_Prochain = Block_actuel->suivant;
        free(Block_actuel);
    }
    printf("--- L'espace memoire a correctement ete libere ---");
}


void New_date(char* datechar, int nombre)
{
    int i;
    int date[8];
    char new_date[9];
    int day,month,year;
    for (i = 0; i < 8; i++)
    {
        date[i] = datechar[i] - '0';//转换成数字
    }

    day = date[0] * 10 + date[1];
    month = date[2] * 10 + date[3];
    year = date[4] * 1000 + date[5] * 100 + date[6] * 10 + date[7];
    day += nombre;
    if (nombre > 0)
    {
        while (day >28)
        {
            if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
            {
                day = day - 30;
            }
            else if (month == 2)
            {
                if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
                {
                    day = day - 29;
                }
                else
                {
                    day = day - 28;
                }
            }
            else
            {
                day = day - 31;
            }
            if (day == 0)
            {
                day += 1;
            }
            month = month + 1;
            if (month / 13 == 1)
            {
                year = year + 1;
                month = 1;//新一年
            }
        }
    }
    else if (nombre == 0)
    {
        return datechar;
    }
    else
    {

        while (day <0)
        {
            if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
            {
                day = day + 30;
            }
            else if (month == 2)
            {
                if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
                {
                    day = day + 29;
                }
                else
                {
                    day = day + 28;
                }
            }
            else
            {
                day = day + 31;
            }
            month = month - 1;
            if (month <= 0)
            {
                year = year - 1;
                month = 12;//前一年
            }
        }
        if (day == 0)
        {
                month = month - 1;
                if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
                {
                    day = day + 30;
                }
                else if (month == 2)
                {
                    if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
                    {
                        day = day + 29;
                    }
                    else
                    {
                        day = day + 28;
                    }
                }
                else
                {
                    day = day + 31;
                }
        }

    }

    date[0] = day / 10;
    date[1] = day % 10;
    date[2] = month / 10;
    date[3] = month % 10;
    date[4] = year / 1000;
    date[5] = (year % 1000) / 100;
    date[6] = ((year % 1000) % 100) / 10;
    date[7] = ((year % 1000) % 100) % 10;

    /*for (i = 0; i < 8; i++)
    {
        new_date[i] = (char)(date[i] + '0');
    }
    new_date[8] = '\0';

    return new_date;*/
    for (i = 0; i < 8; i++)
    {
        datechar[i] = (char)(date[i] + '0');
    }

}
