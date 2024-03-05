#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// initialisation
void add_matrix(Node **tab, int l, int c) {
    // Fill the matrix with null values
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            // Initialisation par 0
            tab[i][j].value = 0;
            tab[i][j].is_mine = 0;
            tab[i][j].is_visited = 0;
            tab[i][j].is_flagged = 0;
            tab[i][j].is_boombed = 0;
        }
    }
    //ajouter des mines
    int ind1, ind2;
    srand(time(NULL));
    for (int i = 0; i < l + 10; i++) {
        ind1 = rand() % l;
        ind2 = rand() % c;
        tab[ind1][ind2].value = -1; // mine existe
        tab[ind1][ind2].is_mine = 1;
    }
}

// ajouter les cells a cote
void add_adjacent_values(Node **tab, int l, int c) {
    // Loop
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            // si la celleule a cote est une mine incremente la valeur de la case
            if (tab[i][j].is_mine == 1) {
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int z = j - 1; z <= j + 1; z++) {
                        // cell adjacente existe
                        if (k >= 0 && k < l && z >= 0 && z < c && k != z) {
                            // Incrementer la valeur  de la celleule a cote
                            tab[k][z].value++;
                        }
                    }
                }
            }
        }
    }
}

// \affichage
void Show_all(Node **tab, int l, int c) {
    // Affichege de chaque case
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (tab[i][j].is_boombed == 1)
                printf("[ * ] "); // choix de bomb
            else if (tab[i][j].is_flagged == 1)
                printf("[ f ] "); // drapeaux
            else if (tab[i][j].is_visited == 1) {
                if (tab[i][j].is_mine == 1)
                    printf("[ m ] "); // mine
                else
                    printf("[ %d ] ", tab[i][j].value); // valeur de la cellule
            } else
                printf("[%d:%d] ", i, j); // Print les coordonees de la cellule
        }
        printf("\n");
    }
}

//change l'etat des cellules adjacente de  la cellule choisi
void change_visited_state(Node **tab, int l, int c, int x, int y) {
    // marke de la cellule est deja visite
    tab[x][y].is_visited = 1;
    // affiche les cellules adjascentes si la valeur de la cellule est 0
    if (tab[x][y].value == 0) {
        for (int k = x - 1; k <= x + 1; k++) {
            for (int z = y - 1; z <= y + 1; z++) {
                if (k >= 0 && k < l && z >= 0 && z < c) {
                    if (tab[k][z].is_mine != 1 && tab[k][z].is_visited == 0) {
                        change_visited_state(tab, l, c, k, z);
                    }
                }
            }
        }
    }
}


int visit_node(Node **tab, int l, int c, int x, int y) {
    // cellule contien une mine
    if (tab[x][y].is_mine == 1) {
        printf("GAME OVER \n");
        tab[x][y].is_boombed = 1;
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < c; j++)
                tab[i][j].is_visited = 1;
        }
        return 0;
    } else if (tab[x][y].is_visited == 1) {
        printf("You have been here before. Choose another one!\n");
    } else {
        printf("YOU WIN !!\n");
        // change l'etat des cellules a djacente a l'etat  visited
        change_visited_state(tab, l, c, x, y);
    }
    return 1;
}

// metre un drapeaux
void AddFlag(Node **tab, int x, int y) {
    tab[x][y].is_flagged = 1;
}

// anuuler un drapeau
void destroyFlag(Node **tab, int x, int y) {
    tab[x][y].is_flagged = 0;
}

// commancer le jeux
void play_game(Node **tab, int l, int c) {
    int x, y, is_lose, choose;
    do {
        printf("\n");
        printf("**************************************************\n");
        printf("1 - Add flag \n");
        printf("2 - Visit the case \n");
        printf("3 - Delete flag \n");
        printf("**************************************************\n");
        printf("Enter your request (1/2): ");
        scanf("%d", &choose);
        printf("\nEnter the x and y coordinates of your request: ");
        scanf("%d %d", &x, &y);

        switch (choose) {
            case 1:
                AddFlag(tab, x, y);
                break;
            case 2:
                is_lose = visit_node(tab, l, l, x, y);
                break;
            case 3:
                destroyFlag(tab, x, y);
                break;
            default:
                printf("Try again with 1 or 2 :) \n");
                break;
        }

        Show_all(tab, l, c);
    } while (is_lose != 0);
}

int main() {
    printf("Let's Play \n");
    int l;
    do {
        printf(" level of difficulty:\n");
        printf("1 - Easy \n");
        printf("2 - Medium \n");
        printf("3 - Hard \n");
        printf("Choose between 1, 2, or 3:  \n");
        scanf("%d", &l);
    } while (l > 3 && l < 1);
    l = l * 10;

    // cree le tableau du jeux
    Node **tab = malloc(l * sizeof(Node *));
    for (int i = 0; i < l; i++) {
        tab[i] = malloc(l * sizeof(Node));
    }

    add_matrix(tab, l, l);
    add_adjacent_values(tab, l, l);
    Show_all(tab, l, l);
    play_game(tab, l, l);

    // afface la memoire
    for (int i = 0; i < l; i++) {
        free(tab[i]);
    }
    free(tab);
    return 0;
}
