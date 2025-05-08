#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *next;
    struct Noeud *prev;
} Noeud;

Noeud* cree(int valeur) {
    Noeud* NewE = (Noeud*)malloc(sizeof(Noeud));
    if (NewE == NULL) {
        printf("Echec d'allocation memoire.\n");
        exit(1);
    }
    NewE->valeur = valeur;
    NewE->next = NULL;
    NewE->prev = NULL;

    return NewE;
}

void afficher(Noeud* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    Noeud* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->next;
    }
    printf("\n");
}

void afficherInverse(Noeud* head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Noeud* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("Liste des nombres (de la fin vers le debut): ");
    while (temp != NULL) {
        printf("%d ", temp->valeur);
        temp = temp->prev;
    }
    printf("\n");
}

Noeud* ajouterD(Noeud* head, int valeur) {
    Noeud* NewE = cree(valeur);
    if (head != NULL) {
        NewE->next = head;
        head->prev = NewE;
    }
    return NewE;
}

Noeud* ajouterF(Noeud* head, int valeur) {
    Noeud* NewE = cree(valeur);
    if (head == NULL) {
        return NewE; 
    } else {
        Noeud* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; 
        }
        temp->next = NewE; 
        NewE->prev = temp; 
    }
    return head;
}

int taille(Noeud* head) {
    int count = 0;
    Noeud* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

Noeud* insertion(Noeud* head, int valeur, int pos) {
    if (pos < 0 || pos > taille(head)) {
        printf("Position invalide.\n");
    
    } else if (pos == 0) {
        return ajouterD(head, valeur); 
    } else {
        Noeud* NewE = cree(valeur);
        Noeud* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next; 
        }
        NewE->next = temp->next; 
        NewE->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = NewE; 
        }
        temp->next = NewE; 
    }
    return head; 
}

Noeud* rechercher(Noeud* head, int valeur) {
    Noeud* temp = head;
    while (temp != NULL) {
        if (temp->valeur == valeur) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}

Noeud* supprimerD(Noeud* head) {
    if (head != NULL) {
        Noeud* temp = head;
        head = head->next; 
        if (head != NULL) {
            head->prev = NULL; 
        }
        free(temp); 
    }
    return head;
}

Noeud* supprimerF(Noeud* head) {
    if (head != NULL) {
        if (head->next == NULL) {
            free(head); 
            return NULL;
        } else {
            Noeud* temp = head;
            while (temp->next != NULL) {
                temp = temp->next; 
            }
            temp->prev->next = NULL; 
            free(temp); 
        }
    }
    return head; 
}

Noeud* supprimerP(Noeud* head, int pos) {
    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide.\n");
        return head; 
    } else if (pos == 0) {
        return supprimerD(head); 
    } else {
        Noeud* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next; 
        }
        temp->prev->next = temp->next; 
        if (temp->next != NULL) {
            temp->next->prev = temp->prev; 
        }
        free(temp); 
    }
    return head; 
}

Noeud* modifierD(Noeud* head, int valeur) {
    if (head == NULL) {
        printf("La liste est vide. Impossible de modifier.\n");
        return head; 
    }
    head->valeur = valeur; 
    return head; 
}

Noeud* modifierF(Noeud* head, int valeur) {
    if (head == NULL) {
        printf("La liste est vide. Impossible de modifier.\n");
        return head; 
    } else {
        Noeud* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; 
        }
        temp->valeur = valeur; 
    }
    return head; 
}

Noeud* modifierP(Noeud* head, int pos, int valeur) {
    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide. Impossible de modifier.\n");
        return head; 
    } else {
        Noeud* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next; 
        }
        temp->valeur = valeur; 
    }
    return head; 
}

Noeud* triSelection(Noeud* head) {
    if (head == NULL || head->next == NULL) return head;

    Noeud* temp1 = head;

    while (temp1 != NULL) {
        Noeud* min = temp1;
        Noeud* temp2 = temp1->next;

        while (temp2 != NULL) {
            if (temp2->valeur < min->valeur) {
                min = temp2; 
            }
            temp2 = temp2->next;
        }

        if (min != temp1) {
            int temp = temp1->valeur;
            temp1->valeur = min->valeur;
            min->valeur = temp; 
        }

        temp1 = temp1->next;
    }

    return head; 
}

int main() {
    Noeud* head = NULL;

    Noeud* P = cree(10);
    Noeud* B = cree(20);
    Noeud* E = cree(30);

    head = P;
    P->next = B;
    B->prev = P;
    B->next = E;
    E->prev = B;

    printf("=== Affichage initial ===\n");
    afficher(head);

    printf("\n=== Affichage inverse ===\n");
    afficherInverse(head);

    printf("\n=== Ajout au debut (40) ===\n");
    head = ajouterD(head, 40);
    afficher(head);

    printf("\n=== Ajout a la fin (400) ===\n");
    head = ajouterF(head, 400);
    afficher(head);

    printf("\n=== Insertion a la position 2 (2400) ===\n");
    head = insertion(head, 2400, 2);
    afficher(head);

    printf("\n=== Recherche de l'element 1000 ===\n");
    if (rechercher(head, 1000)) {
        printf("La valeur existe\n");
    } else {
        printf("La valeur n'existe pas\n");
    }

    printf("\n=== Modification du premier element (35) ===\n");
    head = modifierD(head, 35);
    afficher(head);

    printf("\n=== Modification du dernier element (20) ===\n");
    head = modifierF(head, 20);
    afficher(head);

    printf("\n=== Modification a la position 2 (100) ===\n");
    head = modifierP(head, 2, 100);
    afficher(head);

    printf("\n=== Suppression du premier element ===\n");
    head = supprimerD(head);
    afficher(head);

    printf("\n=== Suppression du dernier element ===\n");
    head = supprimerF(head);
    afficher(head);

    printf("\n=== Suppression a la position 4 ===\n");
    head = supprimerP(head, 4);
    afficher(head);

    printf("\n=== Tri de la liste ===\n");
    head = triSelection(head);
    afficher(head);

    return 0;
}
