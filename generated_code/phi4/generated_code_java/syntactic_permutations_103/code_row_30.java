import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try {
            openFile(fileName, true);
            System.out.println("File opened successfully.");
            
            // Close the file after operations
            closeFile(fileName);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static void openFile(String fileName, boolean createIfNotExists) throws IOException {
        File file = new File(fileName);

        if (!file.exists() && createIfNotExists) {
            // O_CREAT | O_EXCL
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                throw new IOException("Could not create the file: " + fileName);
            }
        } else if (file.exists() && !createIfNotExists) {
            // O_TRUNC | O_WRONLY
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                System.out.println("File opened for writing and truncated to 0 bytes.");
            }
        } else {
            throw new IOException("File already exists and createIfNotExists is false.");
        }

        // Open the file in write-only mode
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            // File opened successfully
        }
    }

    public static void closeFile(String fileName) throws IOException {
        // In Java, files are closed automatically when using try-with-resources.
        System.out.println("File operations complete. If not already closed, the file is now closed.");
    }
}