#include <stdio.h>
#include <stdlib.h>

typedef struct s_list {
    int num;

    struct s_list *next;
} t_list;

t_list *create_node(int set_num) {
    t_list *node = (t_list *)malloc(sizeof(t_list));

    node -> num = set_num;

    node -> next = NULL;
    return node;
}

void push_front(t_list **list, int set_num) {
    t_list *new_element = create_node(set_num);

    new_element -> next = *list;
    *list = new_element;
}

void insert(t_list *first, t_list *second) {
    t_list *curr = first;
    for (int i = 1; i < 2; i++) {
        curr = curr -> next;
    }

    t_list *temp = curr -> next;

    curr -> next = second;

    while (second -> next != NULL) {
        second = second->next;
    }

    second -> next = temp;
}

int main() {
    int n;
    printf("Enter n:");
    scanf("%d", &n);
    if (n > 0) {
        printf("n is %i\n", n);

        t_list *S1 = create_node(1);
        for (int i = 2; i < (2 * n) + 1; i++) {
            push_front(&S1, i);
        }

        t_list *S2 = create_node(100);
        for (int i = 101; i < n + 100; i++) {
            push_front(&S2, i);
        }

        insert(S1, S2);
        printf("\nS1 is now:\n");
        while (S1 != NULL) {
            printf("num is %d\n", S1 -> num);
            S1 = S1 -> next;
        }

    } else printf("n must be greater than 0");
    return 0;
}
