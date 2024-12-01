typedef struct message {
    int sender_pid;      // ID del proceso remitente
    char content[128];   // Contenido del mensaje (tamaño fijo)
} message;
