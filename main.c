#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 100

// Renkler - Red-Black Tree dengesi için kullanýlan renk türleri
// Red-Black aðacýnda düðümler kýrmýzý veya siyah olarak iþaretlenir
// Bu renkler, aðacýn dengeli kalmasýný saðlamak için kullanýlýr
typedef enum { RED, BLACK } Color;

// Kullanýcý yapýsý (Red-Black Tree düðümü)
// Her kullanýcý benzersiz bir kimliðe sahip ve aðaçta bir düðüm olarak temsil edilir
// Kullanýcý, sol ve sað alt düðümlere ve bir üst düðüme iþaretçiler içerir
// Ayrýca Red-Black Tree algoritmasý için gerekli renk bilgisini tutar
typedef struct User {
    int id;              // Kullanýcýnýn benzersiz kimlik numarasý
    struct User *left;   // Sol alt aðaç
    struct User *right;  // Sað alt aðaç
    struct User *parent; // Üst düðüm
    Color color;         // Red-Black dengesi için renk bilgisi
} User;

// Ýliþki grafý - Kullanýcýlar arasýndaki arkadaþlýk iliþkilerini temsil eder
// Komþuluk matrisi kullanarak kullanýcýlar arasýndaki baðlantýlarý gösterir
// Ýki kullanýcý arasýnda bir baðlantý varsa, matristeki ilgili deðer 1 olur
typedef struct Graph {
    int adj[MAX_USERS][MAX_USERS]; // Komþuluk matrisi (baðlantý matrisi)
    int user_count;                // Sistemdeki toplam kullanýcý sayýsý
    int ids[MAX_USERS];            // Kullanýcý ID'lerini saklayan dizi
} Graph;
Graph graph;
User *user_tree = NULL;

// --- Red-Black Tree Fonksiyonlarý ---

User* newUser(int id) {
    User *u = (User*)malloc(sizeof(User));
    u->id = id;
    u->left = u->right = u->parent = NULL;
    u->color = RED;
    return u;
}

void leftRotate(User **root, User *x) {
    User *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(User **root, User *y) {
    User *x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) *root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(User **root, User *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            User *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            User *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertUser(User **root, int id) {
    User *z = newUser(id);
    User *y = NULL;
    User *x = *root;
    while (x) {
        y = x;
        if (z->id < x->id)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y) *root = z;
    else if (z->id < y->id)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

// --- Graph Fonksiyonlarý ---

void addUser(int id) {
    graph.ids[graph.user_count++] = id;
    insertUser(&user_tree, id);
}

void addFriendship(int id1, int id2) {
    int i, j;
    for (i = 0; i < graph.user_count; i++) if (graph.ids[i] == id1) break;
    for (j = 0; j < graph.user_count; j++) if (graph.ids[j] == id2) break;
    graph.adj[i][j] = 1;
    graph.adj[j][i] = 1;
}

// --- Analiz Fonksiyonlarý ---

int findIndex(int id) {
    for (int i = 0; i < graph.user_count; i++) {
        if (graph.ids[i] == id) return i;
    }
    return -1;
}

void dfs_component(int idx, bool visited[]) {
    visited[idx] = true;
    printf("%d ", graph.ids[idx]);
    for (int i = 0; i < graph.user_count; i++) {
        if (graph.adj[idx][i] && !visited[i])
            dfs_component(i, visited);
    }
}

void findCommunities() {
    bool visited[MAX_USERS] = { false };
    for (int i = 0; i < graph.user_count; i++) {
        if (!visited[i]) {
            dfs_component(i, visited);
            printf("\n");
        }
    }
}

int countReachable(int idx, bool visited[]) {
    int count = 1;
    visited[idx] = true;
    for (int i = 0; i < graph.user_count; i++) {
        if (graph.adj[idx][i] && !visited[i])
            count += countReachable(i, visited);
    }
    return count;
}

void analyzeAllUsers() {
    printf("\n--- Tum Kullanicilar Için Analiz ---\n");
    for (int u = 0; u < graph.user_count; u++) {
        int user_id = graph.ids[u];
        printf("\nKullanici %d Analizi:\n", user_id);

        // 1. Mesafe 1 arkadaþlar
        printf("Dogrudan Arkadaslar (Mesafe 1): ");
        for (int v = 0; v < graph.user_count; v++) {
            if (graph.adj[u][v]) {
                printf("%d ", graph.ids[v]);
            }
        }
        printf("\n");

        // 2. Mesafe 2 arkadaþlar
        printf("Mesafe 2 Arkadaslar: ");
        bool visited[MAX_USERS] = { false };
        visited[u] = true;
        for (int v = 0; v < graph.user_count; v++) {
            if (graph.adj[u][v]) {
                visited[v] = true;
                for (int w = 0; w < graph.user_count; w++) {
                    if (graph.adj[v][w] && !visited[w]) {
                        printf("%d ", graph.ids[w]);
                        visited[w] = true;
                    }
                }
            }
        }
        printf("\n");

        // 3. Ortak arkadaþlar (diðer kullanýcýlarla)
        for (int other = 0; other < graph.user_count; other++) {
            if (u == other) continue;
            printf("Ortak arkadaslar (%d ve %d): ", user_id, graph.ids[other]);
            bool found = false;
            for (int k = 0; k < graph.user_count; k++) {
                if (graph.adj[u][k] && graph.adj[other][k]) {
                    printf("%d ", graph.ids[k]);
                    found = true;
                }
            }
            if (!found) printf("Yok");
            printf("\n");
        }

        // 4. Etki Alaný
        bool visited_influence[MAX_USERS] = { false };
        int reach = countReachable(u, visited_influence);
        printf("Erisebildigi toplam kisi sayisi: %d\n", reach - 1);
    }
}

// --- Ana Fonksiyon ---

int main() {
    // Kullanýcýlar
    addUser(101);
    addUser(102);
    addUser(103);
    addUser(104);
    addUser(105);

    // Arkadaþlýklar
    addFriendship(101, 102);
    addFriendship(101, 103);
    addFriendship(102, 104);
    addFriendship(103, 104);
    addFriendship(104, 105);

    // Tüm analizleri yap
    analyzeAllUsers();

    // Topluluklarý bul
    printf("\nTopluluklar:\n");
    findCommunities();

    return 0;
}

