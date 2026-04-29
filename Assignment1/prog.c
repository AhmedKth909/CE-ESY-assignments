#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

// تهيئة
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// فحص الامتلاء
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// فحص الفراغ
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// كتابة
void writeBuffer(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

// قراءة
char readBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

// تصفير المخزن
void clearBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    int choice;
    char name[100];

    printf("1- Write\n2- Read\nChoose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter your name: ");
        scanf("%s", name);

        strcat(name, "CE-ESY");  // إضافة السلسلة

        // كتابة كل محرف
        for (int i = 0; i < strlen(name); i++) {
            writeBuffer(&cb, name[i]);
        }

        printf("Writing done.\n");

        // قراءة وطباعة
        printf("\nReading from buffer:\n");
        while (!isEmpty(&cb)) {
            char c = readBuffer(&cb);
            printf("%c", c);
        }
    }

    else if (choice == 2) {
        printf("Trying to read...\n");
        char c = readBuffer(&cb);  // سيظهر Underflow

        if (c == '\0') {
            int again;
            printf("Buffer is empty. Choose:\n");
            printf("1- Write\n0- Exit\n");
            scanf("%d", &again);

            if (again == 1) {
                printf("Enter your name: ");
                scanf("%s", name);

                strcat(name, "CE-ESY");

                for (int i = 0; i < strlen(name); i++) {
                    writeBuffer(&cb, name[i]);
                }

                printf("Writing done.\n");

                // قراءة بعد الكتابة
                printf("\nReading from buffer:\n");
                while (!isEmpty(&cb)) {
                    char c2 = readBuffer(&cb);
                    printf("%c", c2);
                }
            } else {
                printf("Program ended.\n");
            }
        }
    }

    // آخر شيء دائمًا
    clearBuffer(&cb);
    printf("\nBuffer is now empty.\n");

    return 0;
}
