/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x){
    struct ListNode *h = (struct ListNode *)malloc(sizeof(struct ListNode ));
    struct ListNode *h1 = h;
    struct ListNode *t = (struct ListNode *)malloc(sizeof(struct ListNode ));
    struct ListNode *t1 = t;
    while(head != NULL){
        if(head->val < x){
            h1->next = head;
            h1 = h1->next;
        }
        else{
            t1->next = head;
            t1 = t1->next;
        }
        head = head->next;
    }
    t1->next = NULL;
    h1->next = t->next;
    return h->next;
}