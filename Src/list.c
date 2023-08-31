#include "list.h"

OrderNode* insertOrderNode(OrderNode* head, OrderNode* newNodes) {
    if (head == NULL) {
        return newNodes;  // �������Ϊ�գ������½ڵ���Ϊ�µ�ͷ�ڵ�
    }

    OrderNode* currentNode = head;

    // �ҵ���������һ���ڵ�
    while (currentNode != NULL) {
        currentNode = currentNode->next;
    }

    // ���½ڵ����ӵ���������һ���ڵ����
    currentNode->next = newNodes;

    return head;  // ����ԭʼ��ͷ�ڵ�
}