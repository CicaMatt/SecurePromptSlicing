import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            // Open or create a new file, truncate it if it exists, open for writing only, fail if it already exists
            FileOutputStream fos = new FileOutputStream(fileName, false);
            fos.close();
        } catch (IOException e) {
            System.err.println("Failed to open or create the file: " + e.getMessage());
        }
    }
}