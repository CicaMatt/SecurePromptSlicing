import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            createOrOpenFile(filePath);
            System.out.println("File opened or created successfully.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static void createOrOpenFile(String path) throws IOException {
        // Open file with O_CREAT | O_WRONLY | O_EXCL and handle if the file already exists
        try (FileOutputStream fos = new FileOutputStream(path, false)) {
            System.out.println("File created or opened for writing.");
        } catch (IOException e) {
            if (e.getMessage().contains("already exists")) {
                // If file creation fails due to existence, open it with O_TRUNC | O_WRONLY
                try (FileOutputStream fos = new FileOutputStream(path)) {
                    System.out.println("Existing file truncated and opened for writing.");
                }
            } else {
                throw e; // Rethrow if exception is not about existence
            }
        }
    }
}