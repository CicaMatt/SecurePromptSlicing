import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            createOrOpenFile(filePath);
            System.out.println("File operation successful.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static void createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);

        if (file.exists()) {
            throw new IOException("File already exists. Operation aborted due to O_EXCL flag.");
        } else {
            boolean created = file.createNewFile();
            if (!created) {
                throw new IOException("Failed to create a new file.");
            }
        }

        // Truncate the file to 0 bytes (effectively emptying it)
        truncateFile(filePath);

        try (java.io.FileOutputStream fos = new java.io.FileOutputStream(file, false)) {
            // File opened for writing only
        } catch (IOException e) {
            throw new IOException("Failed to open file for writing.", e);
        }
    }

    private static void truncateFile(String filePath) throws IOException {
        File file = new File(filePath);
        if (!file.exists()) {
            throw new IOException("Cannot truncate non-existent file.");
        }
        
        try (java.io.FileOutputStream fos = new java.io.FileOutputStream(file, false)) {
            // Truncate to 0 bytes by opening with overwrite mode
        } catch (IOException e) {
            throw new IOException("Failed to truncate the file.", e);
        }
    }
}