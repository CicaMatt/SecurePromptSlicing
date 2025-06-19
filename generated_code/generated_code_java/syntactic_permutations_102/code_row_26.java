import java.io.IOException;
class Main {
    public static void main(String[] args) throws IOException {
        int fd = open("important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        write(fd, "important_config");
    }
}