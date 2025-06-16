import java.io.*;

class ImportantConfig {
    public static void main(String[] args) throws IOException {
        int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        if (fd == -1) {
            perror("open()");
            return 1;
        }

        String config = "important_config";

        int rc = write(fd, config.getBytes(), config.length());

        if (rc == -1) {
            perror("write()");
            return 1;
        }

        close(fd);
    }
}