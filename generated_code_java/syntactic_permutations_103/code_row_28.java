import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) throws IOException {
        String filename = "test.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
        open(filename, flags);
    }
}