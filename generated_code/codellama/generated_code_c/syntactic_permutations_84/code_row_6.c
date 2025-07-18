#include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <string.h>

    int main(void)
    {
        // Creating socket file descriptor
        int server_fd, new_socket;
        struct sockaddr_in address;
        char buffer[1024] = { 0 };
        char *hello = "Hello from server";

        // Create a new socket
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET,
                       SO_REUSEADDR | SO_REUSEPORT, &opt,
                       sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(5000);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd,
                                 (struct sockaddr *)&address,
                                 (socklen_t*)&address)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char *payload = get_parameter(new_socket, "payload");
        if (!payload)
        {
            send(new_socket, "Missing payload parameter.", 26, 0);
            return -1;
        }

        struct yaml_document *doc = yaml_parse_string(payload);
        char *type = get_yaml_value(doc, "type");
        if (!strcmp("Create", type))
        {
            send(new_socket, "Invalid type.", 14, 0);
            return -1;
        }
    }

    char *get_parameter(int socket_fd, const char param[])
    {
        char buffer[BUFSIZ];
        int size = recv(socket_fd, buffer, BUFSIZ, 0);
        if (size <= 0)
            return NULL;
        char *parameter = strstr(buffer, param);
        if (!parameter)
            return NULL;
        parameter += strlen(param) + 1;

        int i = 0;
        while (*parameter && *parameter != '&')
        {
            buffer[i++] = *parameter;
            ++parameter;
        }
        if (buffer == '\0' || buffer == NULL)
            return NULL;
        return strdup(buffer);
    }

    char *get_yaml_value(struct yaml_document *doc, const char key[])
    {
        struct yaml_node *root = yaml_document_get_root_node(doc);
        if (!root)
            return NULL;
        if (root->type != YAML_MAPPING_NODE)
            return NULL;
        struct yaml_node *value = yaml_mapping_get_value(root, key);

        if (!value)
            return NULL;
        char buffer[BUFSIZ];
        int size = yaml_scalar_value(value);
        if (size <= 0)
            return NULL;
        strncpy(buffer, value->data.scalar.value, BUFSIZ - 1);
        return buffer;
    }

    int main()
    {
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0)
            exit(-1);
        struct sockaddr_in address;
        memset(&address, 0, sizeof(struct sockaddr_in));
        address.sin_family = AF_INET;
        address.sin_port = htons(5000);
        if (bind(socket_fd, (struct sockaddr *)&address,
                 sizeof(struct sockaddr)) < 0)
            exit(-1);
        if (listen(socket_fd, 3) < 0)
            exit(-1);

        int client_fd = accept(socket_fd, NULL, NULL);
        if (client_fd < 0)
            exit(-1);
    }