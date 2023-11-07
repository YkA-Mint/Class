#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tp3.h"

extern char date[];

int main(){


    int nombre;
    char datablocCurrent[9];
    T_Block * BlocCurrent=NULL;
    int idEtuCurrent,idEtuCurrent2;
    float montant;
    char description[100];
    char *new_date = (char*)malloc(9*sizeof(char));
    BlockChain ma_chaine_de_blocs = NULL;
    ma_chaine_de_blocs = ajouterBlock(ma_chaine_de_blocs);
    bool continuer=true;
    int flag = 1;


    // ============= MENU UTILISATEUR ============= */
    char choix = '0';
    while (continuer == true && choix != '8') {
        printf("\n======================================");
        printf("\n1. Afficher la liste des blocs de la BlockChain");
        printf("\n2. Afficher toutes les transactions d'un bloc");
        printf("\n3. Afficher toutes les transactions du jour pour un etudiant");
        printf("\n4. Afficher l'historique pour un etudiant");
        printf("\n5. Crediter un compte");
        printf("\n6. Payer un repas");
        printf("\n7. Transferer des EATCoins entre deux etudiants");
        printf("\n8. Quitter");
        printf("\n9. Manipuler la date par jour（-:avancer,+:reporter ");
        printf("\n======================================");
        printf("\n   Votre choix ? ");

        choix = getchar();

        switch (choix) {
            case '1' :
                Tout_Afficher(ma_chaine_de_blocs);
                break;

            case '2' :
                printf("entrer le datebloc:\n");
                scanf("%s",datablocCurrent);
                BlocCurrent= RechercherBlock(datablocCurrent,ma_chaine_de_blocs);
                if(BlocCurrent!=NULL){
                    AfficherTransactionsBlock(*BlocCurrent);
                }
                else{
                    printf("n'exist pas");
                }
                break;

            case '3' :
                printf("entrer le datebloc:\n");
                scanf("%s", datablocCurrent);
                BlocCurrent = RechercherBlock(datablocCurrent, ma_chaine_de_blocs);
                if (BlocCurrent != NULL) {
                    printf("entrer le idEtu:\n");
                    scanf("%d",&idEtuCurrent);
                    AfficherTransactionEtudiantBlock(idEtuCurrent, *BlocCurrent);
                }
                else {
                    printf("le datebloc n'exist pas");
                }
                break;


            case '4' :
                printf("entrer le idEtu:\n");
                scanf("%d",&idEtuCurrent);
                consulter(idEtuCurrent,ma_chaine_de_blocs);
                break;

            case '5' :
                printf("entrer le idEtu:\n");
                scanf("%d",&idEtuCurrent);
                printf("entrer le montant:\n");
                scanf("%f",&montant);
                //printf("entrer le desccription:\n");
                strcpy(description, "Recharge");
                crediter(idEtuCurrent,montant,description,ma_chaine_de_blocs);
                break;

            case '6' :
                printf("entrer le idEtu:\n");
                scanf("%d",&idEtuCurrent);
                printf("entrer le prix:\n");
                scanf("%f",&montant);
                printf("entrer le desccription:\n");
                scanf("%s",description);
                payer(idEtuCurrent,montant,description,ma_chaine_de_blocs);
                break;

            case '7' :
                printf("entrer le idSource:\n");
                scanf("%d",&idEtuCurrent);
                printf("entrer le idDestination:\n");
                scanf("%d",&idEtuCurrent2);
                printf("entrer le montant:\n");
                scanf("%f",&montant);
                //printf("entrer le desccription:\n");
                //scanf("%s",&description);
                strcpy(description, "Transferer");
                flag = transfert(idEtuCurrent,idEtuCurrent2,montant,description,ma_chaine_de_blocs);
                if(flag==1)
                    printf("transfert effectuee");
                else
                    printf("transfert n'a pas effectuee");
                break;

            case '8' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                Tout_Liberer(ma_chaine_de_blocs);
                break;

            case '9' :
                printf("entrer le nombre de journee:\n");
                scanf("%d",&nombre);
                New_date(date, nombre);
                //strcpy(date, new_date);
                printf("%s",date);

                ma_chaine_de_blocs = ajouterBlock(ma_chaine_de_blocs);
                break;
            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
        viderBuffer(); // supprimer de l'entr�e standard le retour charriot et les �ventuels caract�res suppl�mentaires tap�s par l'utilisateur
    }
    return 0;
}
