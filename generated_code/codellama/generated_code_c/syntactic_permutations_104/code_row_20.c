int fd = open("myfile", O_RDWR | O_CREAT, 0644);
write(fd, "important_config", strlen("important_config") + 1);