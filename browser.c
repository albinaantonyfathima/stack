#include <stdio.h>
#include <string.h>

#define MAX 50
#define LEN 100

// Renamed stacks
char backward[MAX][LEN]; // stores visited pages (past)
char forward[MAX][LEN];  // stores forward pages

int b_top = -1;
int f_top = -1;

// Visit a new page
void visit(char url[]) {
    if (b_top < MAX - 1) {
        b_top++;
        strcpy(backward[b_top], url);

        // clear forward stack
        f_top = -1;

        printf("Visited: %s\n", url);
    } else {
        printf("Backward stack is full!\n");
    }
}

// Go back
void goBack(int steps) {
    while (steps > 0 && b_top > 0) {
        f_top++;
        strcpy(forward[f_top], backward[b_top]);

        b_top--;
        steps--;
    }
    printf("Current Page: %s\n", backward[b_top]);
}

// Go forward
void goForward(int steps) {
    while (steps > 0 && f_top >= 0) {
        b_top++;
        strcpy(backward[b_top], forward[f_top]);

        f_top--;
        steps--;
    }
    printf("Current Page: %s\n", backward[b_top]);
}

// Show history
void showHistory() {
    printf("\n--- Browser History ---\n");

    for (int i = 0; i <= b_top; i++) {
        if (i == b_top)
            printf("-> %s (Current)\n", backward[i]);
        else
            printf("   %s\n", backward[i]);
    }

    // Show forward stack also (extra feature)
    printf("\n--- Forward Pages ---\n");
    for (int i = f_top; i >= 0; i--) {
        printf("   %s\n", forward[i]);
    }
}

// Main menu
int main() {
    int choice, steps;
    char url[LEN];

    // Initialize homepage
    visit("homepage.com");

    while (1) {
        printf("\n===== Browser Menu =====\n");
        printf("1. Visit New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show History\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visit(url);
                break;

            case 2:
                printf("Enter steps: ");
                scanf("%d", &steps);
                goBack(steps);
                break;

            case 3:
                printf("Enter steps: ");
                scanf("%d", &steps);
                goForward(steps);
                break;

            case 4:
                showHistory();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
