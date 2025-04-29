#include <iostream>
#include <fstream>
#include <cstring>

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);
void printQueue(const Queue *q, std::ofstream &outputFile);
void destroyQueue(Queue *q);

// =================================================================================

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        return 1;
    }
    if (!outputFile.is_open()) {
        if (inputFile.is_open()) inputFile.close();
        return 1;
    }

    Queue *myQueue = nullptr;
    char command[50];
    int value;

    while (inputFile >> command) {
        if (strcmp(command, "init") == 0) {
            if (myQueue != nullptr) {
                destroyQueue(myQueue);
            }
            myQueue = initializeQueue();
        } else if (strcmp(command, "enqueue") == 0) {
            if (!(inputFile >> value)) {
                 inputFile.clear();
                 inputFile.ignore(10000, '\n');
            } else {
                 if (myQueue != nullptr) {
                     enqueue(*myQueue, value);
                 }
            }
        } else if (strcmp(command, "dequeue") == 0) {
            if (myQueue != nullptr) {
                dequeue(*myQueue);
            }
        }
        printQueue(myQueue, outputFile);
    }

    inputFile.close();
    outputFile.close();

    if (myQueue != nullptr) {
        destroyQueue(myQueue);
    }

    return 0;
}

// =================================================================================

Queue* initializeQueue() {
    Queue *q = new(std::nothrow) Queue;
    if (q != nullptr) {
        q->head = nullptr;
        q->tail = nullptr;
    }
    return q;
}

void enqueue(Queue &q, int key) {
    NODE* newNode = new(std::nothrow) NODE;
    if (newNode == nullptr) {
        return;
    }

    newNode->key = key;
    newNode->p_next = nullptr;

    if (q.head == nullptr) {
        q.head = newNode;
        q.tail = newNode;
    } else {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue &q) {
    if (q.head == nullptr) {
       return -1;
    }

    NODE* temp = q.head;
    int dequeuedValue = temp->key;
    q.head = temp->p_next;

    if (q.head == nullptr) {
        q.tail = nullptr;
    }

    delete temp;
    return dequeuedValue;
}

int size(Queue q) {
    int count = 0;
    NODE* current = q.head;
    while (current != nullptr) {
        count++;
        current = current->p_next;
    }
    return count;
}

bool isEmpty(Queue q) {
    return q.head == nullptr;
}

void printQueue(const Queue *q, std::ofstream &outputFile) {
    if (q == nullptr || q->head == nullptr) {
        outputFile << "EMPTY" << std::endl;
    } else {
        NODE* current = q->head;
        while (current != nullptr) {
            outputFile << current->key;
            if (current->p_next != nullptr) {
                outputFile << " ";
            }
            current = current->p_next;
        }
        outputFile << std::endl;
    }
}

void destroyQueue(Queue *q) {
    if (q == nullptr) {
        return;
    }
    NODE* current = q->head;
    NODE* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->p_next;
        delete current;
        current = nextNode;
    }
    delete q;
}