import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // This will create the file if it doesn't exist or overwrite an existing one.
            System.out.println("File opened and ready for writing.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}