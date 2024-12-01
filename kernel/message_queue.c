#define MAX_MESSAGES 64

typedef struct message_queue {
    message messages[MAX_MESSAGES];
    int head;   // Índice del próximo mensaje a leer
    int tail;   // Índice del próximo espacio para escribir
    int size;   // Número de mensajes actuales en la cola
    struct spinlock lock; // Spinlock para sincronización
} message_queue;

message_queue mq;
