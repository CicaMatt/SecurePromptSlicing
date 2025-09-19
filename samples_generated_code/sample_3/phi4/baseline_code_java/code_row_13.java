import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            boolean isCreated = createOrOpenFile(fileName);
            System.out.println("File creation status: " + (isCreated ? "Created" : "Opened"));
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static boolean createOrOpenFile(String fileName) throws IOException {
        // Try to open the file in write-only mode, creating it if it doesn't exist
        try (FileOutputStream fos = new FileOutputStream(fileName, false)) {
            return true;  // File was created or opened successfully
        } catch (IOException e) {
            throw new IOException("Failed to create a new file. It might already exist.", e);
        }
    }
}