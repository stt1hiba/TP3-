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
    return NewE; // New node becomes the new head
}

Noeud* ajouterF(Noeud* head, int valeur) {
    Noeud* NewE = cree(valeur);
    if (head == NULL) {
        return NewE; // If the list is empty, return the new node as the head
    } else {
        Noeud* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the end of the list
        }
        temp->next = NewE; // Link the new node at the end
        NewE->prev = temp; // Set the previous pointer of the new node
    }
    return head; // Return the head of the list
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
        return head; // Return the original head if position is invalid
    } else if (pos == 0) {
        return ajouterD(head, valeur); // Insert at the beginning
    } else {
        Noeud* NewE = cree(valeur);
        Noeud* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next; // Traverse to the node before the desired position
        }
        NewE->next = temp->next; // Link new node to the next node
        NewE->prev = temp; // Set the previous pointer of the new node
        if (temp->next != NULL) {
            temp->next->prev = NewE; // Update the previous pointer of the next node
        }
        temp->next = NewE; // Link the previous node to the new node
    }
    return head; // Return the head of the list
}

Noeud* rechercher(Noeud* head, int valeur) {
    Noeud* temp = head;
    while (temp != NULL) {
        if (temp->valeur == valeur) {
            return temp; // Return the node if found
        }
        temp = temp->next;
    }
    return NULL; // Return NULL if not found
}

Noeud* supprimerD(Noeud* head) {
    if (head != NULL) {
        Noeud* temp = head;
        head = head->next; // Move head to the next node
        if (head != NULL) {
            head->prev = NULL; // Set the previous pointer of the new head to NULL
        }
        free(temp); // Free the old head
    }
    return head; // Return the new head
}

Noeud* supprimerF(Noeud* head) {
    if (head != NULL) {
        if (head->next == NULL) {
            free(head); // Free the only node
            return NULL; // List is now empty
        } else {
            Noeud* temp = head;
            while (temp->next != NULL) {
                temp = temp->next; // Traverse to the end of the list
            }
            temp->prev->next = NULL; // Set the next pointer of the second last node to NULL
            free(temp); // Free the last node
        }
    }
    return head; // Return the head of the list
}

Noeud* supprimerP(Noeud* head, int pos) {
    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide.\n");
        return head; // Return the original head if position is invalid
    } else if (pos == 0) {
        return supprimerD(head); // Delete from the beginning
    } else {
        Noeud* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next; // Traverse to the desired position
        }
        temp->prev->next = temp->next; // Link the previous node to the next node
        if (temp->next != NULL) {
            temp->next->prev = temp->prev; // Link the next node to the previous node
        }
        free(temp); // Free the node
    }
    return head; // Return the head of the list
}

Noeud* modifierD(Noeud* head, int valeur) {
    if (head == NULL) {
        printf("La liste est vide. Impossible de modifier.\n");
        return head; // Return the original head
    }
    head->valeur = valeur; // Modify the value of the first node
    return head; // Return the head of the list
}

Noeud* modifierF(Noeud* head, int valeur) {
    if (head == NULL) {
        printf("La liste est vide. Impossible de modifier.\n");
        return head; // Return the original head
    } else {
        Noeud* temp = head;
        while (temp->next != NULL) {
            temp = temp->next; // Traverse to the end of the list
        }
        temp->valeur = valeur; // Modify the value of the last node
    }
    return head; // Return the head of the list
}

Noeud* modifierP(Noeud* head, int pos, int valeur) {
    if (pos < 0 || pos >= taille(head)) {
        printf("Position invalide. Impossible de modifier.\n");
        return head; // Return the original head
    } else {
        Noeud* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next; // Traverse to the desired position
        }
        temp->valeur = valeur; // Modify the value of the node
    }
    return head; // Return the head of the list
}

Noeud* triSelection(Noeud* head) {
    if (head == NULL || head->next == NULL) return head;

    Noeud* temp1 = head;

    while (temp1 != NULL) {
        Noeud* min = temp1;
        Noeud* temp2 = temp1->next;

        while (temp2 != NULL) {
            if (temp2->valeur < min->valeur) {
                min = temp2; // Update min if a smaller value is found
            }
            temp2 = temp2->next;
        }

        if (min != temp1) {
            int temp = temp1->valeur;
            temp1->valeur = min->valeur;
            min->valeur = temp; // Swap values
        }

        temp1 = temp1->next;
    }

    return head; // Return the head of the list
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
