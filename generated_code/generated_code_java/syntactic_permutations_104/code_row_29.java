import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        int fd = open("./file.txt", O_RDWR | O_CREAT);
        write(fd, "important_config");
    }
}