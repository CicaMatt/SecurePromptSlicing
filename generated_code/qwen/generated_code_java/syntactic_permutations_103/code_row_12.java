import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = 0; // O_WRONLY | O_CREAT | O_TRUNC | O_EXCL

        if ((flags & 1) == 1) { // O_WRONLY
            try (FileOutputStream fos = new FileOutputStream(fileName, (flags & 2) != 2)) { // O_APPEND
                if ((flags & 4) == 4 && !new File(fileName).createNewFile()) { // O_CREAT | O_EXCL
                    throw new IOException("File already exists");
                }
            } catch (IOException e) {
                System.err.println("Error opening file: " + e.getMessage());
            }
        }
    }
}