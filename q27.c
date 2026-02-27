#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int getLength(struct Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

struct Node* getIntersection(struct Node* head1, struct Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    int diff = abs(len1 - len2);

    if (len1 > len2) {
        while (diff--) head1 = head1->next;
    } else {
        while (diff--) head2 = head2->next;
    }

    while (head1 && head2) {
        if (head1->data == head2->data)
            return head1;
        head1 = head1->next;
        head2 = head2->next;
    }

    return NULL;
}

int main() {
    int n, m, i;
    scanf("%d", &n);

    int *arr1 = (int*)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        scanf("%d", &arr1[i]);

    scanf("%d", &m);

    int *arr2 = (int*)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
        scanf("%d", &arr2[i]);

    struct Node *head1 = NULL, *head2 = NULL, *tail1 = NULL, *tail2 = NULL;

    for (i = 0; i < n; i++) {
        struct Node* newNode = createNode(arr1[i]);
        if (!head1)
            head1 = tail1 = newNode;
        else {
            tail1->next = newNode;
            tail1 = newNode;
        }
    }

    int intersectIndex = -1;
    for (i = 0; i < n; i++) {
        if (arr1[i] == arr2[0]) {
            intersectIndex = i;
            break;
        }
    }

    if (intersectIndex != -1) {
        struct Node* temp = head1;
        for (i = 0; i < intersectIndex; i++)
            temp = temp->next;

        head2 = NULL;
        tail2 = NULL;

        for (i = 0; i < m; i++) {
            if (arr2[i] == temp->data) {
                head2 = temp;
                break;
            }
            struct Node* newNode = createNode(arr2[i]);
            if (!head2)
                head2 = tail2 = newNode;
            else {
                tail2->next = newNode;
                tail2 = newNode;
            }
        }
    } else {
        for (i = 0; i < m; i++) {
            struct Node* newNode = createNode(arr2[i]);
            if (!head2)
                head2 = tail2 = newNode;
            else {
                tail2->next = newNode;
                tail2 = newNode;
            }
        }
    }

    struct Node* intersection = getIntersection(head1, head2);

    if (intersection)
        printf("%d", intersection->data);
    else
        printf("No Intersection");

    return 0;
}