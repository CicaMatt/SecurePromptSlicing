import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // The file is created or truncated to 0 bytes if it exists
            System.out.println("File opened for writing. If it existed, it has been truncated.");
        } catch (IOException e) {
            System.err.println("Error: File already exists and cannot be created with O_EXCL equivalent in Java.");
        }

        // To simulate the behavior of O_CREAT | O_TRUNC | O_WRONLY without O_EXCL:
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            System.out.println("File opened for writing. If it existed, it has been truncated.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    // To simulate O_CREAT | O_WRONLY | O_EXCL:
    public static void createUniqueFile(String filePath) throws IOException {
        File file = new File(filePath);

        if (!file.createNewFile()) {
            throw new IOException("File already exists and cannot be created with O_EXCL equivalent in Java.");
        }

        try (FileOutputStream fos = new FileOutputStream(file)) {
            System.out.println("New unique file created successfully: " + filePath);
        }
    }
}