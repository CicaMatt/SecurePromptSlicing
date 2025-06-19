import java.io.*;

public class FileCreator{
    public static void main(String[] args) throws IOException {
        int fileDescriptor = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
    }
}