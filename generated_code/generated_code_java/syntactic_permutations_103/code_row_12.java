import java.io.*;

public class OpenFile {
    public static void main(String[] args) throws Exception {
        int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            System.out.println("Error: File not opened");
            return;
        }
    }
}