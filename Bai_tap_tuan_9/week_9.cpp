#include<iostream>

using namespace std;

struct Node
{
    int heso;
    int exp;
    Node* next;
};


Node* createNode(int heso, int exp)
{
    Node* p = new Node();
    p->heso = heso;
    p->exp = exp;
    p->next = NULL;
    return p;
}


void insertNode(Node* &head, int heso, int exp)
{
    Node* newNode = createNode(heso, exp);
    if (head == NULL || exp > head->exp)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node* p = head;
        while (p->next != NULL && p->next->exp > exp)
        {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
}


Node* sumOfTwoFunc(Node* func1, Node* func2) {
    Node *result = NULL;
    Node* p1 = func1;
    Node* p2 = func2;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            insertNode(result, p1->heso, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            insertNode(result, p2->heso, p2->exp);
            p2 = p2->next;
        } else {
            int TongHeSo = p1->heso + p2->heso;
            if (TongHeSo != 0) {
                insertNode(result, TongHeSo, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1 != NULL) {
        insertNode(result, p1->heso, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        insertNode(result, p2->heso, p2->exp);
        p2 = p2->next;
    }
    return result;
}


void deleteNode(Node*& head) {
    while(head != NULL && head->heso == 0) {
        Node*p = head;
        head = head->next;
        delete p;
    }
    Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        if (temp->next->heso == 0) {
            Node* p = temp->next;
            temp->next = p->next->next;
            delete p;
        } else {
            temp = temp->next;
        }
    }
}


void inputFunction(Node* &head)
{
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int heso, exp;
        cout << "Nhap he so va so mu: ";
        cin >> heso >> exp;
        insertNode(head, heso, exp);
        if (head->heso == 0) {
            deleteNode(head);
        }
    }
}

void printFunction(Node* head)
{
    Node* p = head;
    while (p != NULL)
    {
        if (p->heso > 0 && p != head) {
            cout << "+";
        }
        if (p->exp == 0) {
            cout << p->heso;
        }
        else if (p->heso == 1 && p->exp != 0) {
            cout << "x^" << p->exp;
        }
        else if (p->exp == 1) {
            cout << p->heso << "x";
        } else {
            cout << p->heso << "x^" << p->exp;
        }
        p = p->next;
    }
}


int main() {
    Node* node1 = NULL;
    Node* node2 = NULL;

    inputFunction(node1);
    inputFunction(node2);
    printFunction(node1);
    cout << endl;
    printFunction(node2);
    cout << endl;
    Node* result = sumOfTwoFunc(node1, node2);
    printFunction(result);
    cout << endl;
}




