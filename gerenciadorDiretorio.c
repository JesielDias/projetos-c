#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó de diretório
struct DirectoryNode {
    char name[100];
    struct DirectoryNode *parent;
    struct DirectoryNode *child;
    struct DirectoryNode *sibling;
};

// Função para criar um novo nó de diretório
struct DirectoryNode* createDirectoryNode(const char* name, struct DirectoryNode* parent) {
    struct DirectoryNode* newNode = (struct DirectoryNode*)malloc(sizeof(struct DirectoryNode));
    strcpy(newNode->name, name);
    newNode->parent = parent;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Função para buscar um diretório pelo nome
struct DirectoryNode* findDirectory(struct DirectoryNode* currentDirectory, const char* name) {
    struct DirectoryNode* node = currentDirectory->child;
    while (node != NULL) {
        if (strcmp(node->name, name) == 0) {
            return node;
        }
        node = node->sibling;
    }
    return NULL;
}

// Função para mudar o diretório atual
struct DirectoryNode* changeDirectory(struct DirectoryNode* currentDirectory, const char* name) {
    if (strcmp(name, "..") == 0) {
        return currentDirectory->parent;
    } else {
        struct DirectoryNode* directory = findDirectory(currentDirectory, name);
        if (directory != NULL) {
            return directory;
        } else {
            printf("Diretório '%s' não encontrado.\n", name);
            return currentDirectory;
        }
    }
}

// Função para criar um diretório
void createDirectory(struct DirectoryNode* currentDirectory, const char* name) {
    struct DirectoryNode* newDirectory = createDirectoryNode(name, currentDirectory);
    if (currentDirectory->child == NULL) {
        currentDirectory->child = newDirectory;
    } else {
        struct DirectoryNode* node = currentDirectory->child;
        while (node->sibling != NULL) {
            node = node->sibling;
        }
        node->sibling = newDirectory;
    }
    printf("Diretório '%s' criado.\n", name);
}

// Função para excluir um diretório
void deleteDirectory(struct DirectoryNode* currentDirectory, const char* name) {
    struct DirectoryNode* directory = findDirectory(currentDirectory, name);
    if (directory != NULL) {
        if (currentDirectory->child == directory) {
            currentDirectory->child = directory->sibling;
        } else {
            struct DirectoryNode* node = currentDirectory->child;
            while (node->sibling != directory) {
                node = node->sibling;
            }
            node->sibling = directory->sibling;
        }
        free(directory);
        printf("Diretório '%s' excluído.\n", name);
    } else {
        printf("Diretório '%s' não encontrado.\n", name);
    }
}

// Função para listar os diretórios
void listDirectories(struct DirectoryNode* currentDirectory) {
    struct DirectoryNode* node = currentDirectory->child;
    printf("Diretórios dentro de '%s':\n", currentDirectory->name);
    while (node != NULL) {
        printf("- %s\n", node->name);
        node = node->sibling;
    }
}

int main() {
    struct DirectoryNode* rootDirectory = createDirectoryNode("root", NULL);
    struct DirectoryNode* currentDirectory = rootDirectory;

    char command[100];
    char parameter[100];

    while (1) {
        printf("\nDigite um comando: ");
        scanf("%s", command);

        if (strcmp(command, "mudar_diretorio") == 0) {
            scanf("%s", parameter);
            currentDirectory = changeDirectory(currentDirectory, parameter);
        } else if (strcmp(command, "criar_diretorio") == 0) {
            scanf("%s", parameter);
            createDirectory(currentDirectory, parameter);
        } else if (strcmp(command, "excluir_diretorio") == 0) {
            scanf("%s", parameter);
            deleteDirectory(currentDirectory, parameter);
        } else if (strcmp(command, "listar_diretorios") == 0) {
            listDirectories(currentDirectory);
        } else {
            printf("Comando inválido.\n");
        }
    }

    return 0;
}

