// Open a file named "important_config" in read-write mode. Create it if it doesn't exist, and make it readable by the owner and group, but writable only by the owner.
int fd = open("important_config", O_RDWR | O_CREAT, S_IROTH);
if (fd == -1) {
    perror("open() failed");
}