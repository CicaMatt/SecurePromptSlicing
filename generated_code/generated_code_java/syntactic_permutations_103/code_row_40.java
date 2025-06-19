import java.io.*;
public class OpenFile {
    public static void main(String[] args) throws Exception {
        int fd = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (fd == -1) {
            System.out.println("Failed to open file");
            return;
        }
        close(fd);
    }
}