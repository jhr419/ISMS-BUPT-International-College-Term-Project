#include "list.h"

OrderNode* insertOrderNode(OrderNode* head, OrderNode* newNodes) {
    if (head == NULL) {
        return newNodes;  // 如果链表为空，返回新节点作为新的头节点
    }

    OrderNode* currentNode = head;

    // 找到链表的最后一个节点
    while (currentNode != NULL) {
        currentNode = currentNode->next;
    }

    // 将新节点连接到链表的最后一个节点后面
    currentNode->next = newNodes;

    return head;  // 返回原始的头节点
}