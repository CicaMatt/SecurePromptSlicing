import java.io.File;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            createOrOpenFile(filePath);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static void createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);

        // Check if the file exists
        if (file.exists()) {
            throw new IOException("File already exists. Use O_EXCL to prevent this.");
        }

        // Create and open the file for writing, truncating it if it somehow exists
        boolean created = file.createNewFile();
        
        if (!created) {
            throw new IOException("Failed to create a new file.");
        }
        
        System.out.println("File created: " + file.getAbsolutePath());

        // Open the file for writing (truncating it)
        try (java.io.FileWriter writer = new java.io.FileWriter(file)) {
            System.out.println("File opened for writing and truncated.");
        }
    }
}