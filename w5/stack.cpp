#include <iostream>
#include <fstream>
#include <cstring>

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack();
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack s);
bool isEmpty(Stack s);
void printStackRecursive(NODE* node, std::ofstream &outputFile, bool& isBottom);
void printStack(const Stack *s, std::ofstream &outputFile);
void destroyStack(Stack *s);

// =================================================================================

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        return 1;
    }
    if (!outputFile.is_open()) {
        if(inputFile.is_open()) inputFile.close();
        return 1;
    }

    Stack *myStack = nullptr;
    char command[50];
    int value;

    while (inputFile >> command) {
        if (strcmp(command, "init") == 0) {
            if (myStack != nullptr) {
                destroyStack(myStack);
            }
            myStack = initializeStack();
        } else if (strcmp(command, "push") == 0) {
            if (!(inputFile >> value)) {
                 inputFile.clear();
                 inputFile.ignore(10000, '\n');
            } else {
                if (myStack != nullptr) {
                    push(*myStack, value);
                }
            }
        } else if (strcmp(command, "pop") == 0) {
            if (myStack != nullptr) {
                pop(*myStack);
            }
        }

        printStack(myStack, outputFile);
    }

    inputFile.close();
    outputFile.close();

    if (myStack != nullptr) {
        destroyStack(myStack);
    }

    return 0;
}

// =================================================================================

Stack* initializeStack() {
    Stack *s = new(std::nothrow) Stack;
    if (s != nullptr) {
        s->top = nullptr;
    }
    return s;
}

void push(Stack &s, int key) {
    NODE* newNode = new(std::nothrow) NODE;
    if (newNode == nullptr) {
        return;
    }

    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
}

int pop(Stack &s) {
    if (isEmpty(s)) {
       return -1;
    }

    NODE* temp = s.top;
    int poppedValue = temp->key;
    s.top = temp->p_next;
    delete temp;
    return poppedValue;
}

int size(Stack s) {
    int count = 0;
    NODE* current = s.top;
    while (current != nullptr) {
        count++;
        current = current->p_next;
    }
    return count;
}

bool isEmpty(Stack s) {
    return s.top == nullptr;
}

void printStackRecursive(NODE* node, std::ofstream &outputFile, bool& isBottom) {
    if (node == nullptr) {
        isBottom = true;
        return;
    }
    printStackRecursive(node->p_next, outputFile, isBottom);
    if (!isBottom) {
        outputFile << " ";
    }
    outputFile << node->key;
    isBottom = false;
}

void printStack(const Stack *s, std::ofstream &outputFile) {
    if (s == nullptr || s->top == nullptr) {
        outputFile << "EMPTY" << std::endl;
    } else {
        bool bottomMarker = false;
        printStackRecursive(s->top, outputFile, bottomMarker);
        outputFile << std::endl;
    }
}

void destroyStack(Stack *s) {
    if (s == nullptr) {
        return;
    }
    NODE* current = s->top;
    NODE* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->p_next;
        delete current;
        current = nextNode;
    }
    delete s;
}