import java.io.File;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        // Create a new file or open an existing one, with the specified flags.
        try {
            createOrOpenFile(filePath);
            System.out.println("File operation successful.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void createOrOpenFile(String filePath) throws IOException {
        File file = new File(filePath);

        // O_CREAT | O_EXCL flag simulation
        if (!file.createNewFile()) {
            throw new IOException("File already exists and cannot be created exclusively.");
        }

        // O_TRUNC flag simulation: Truncate the file to 0 bytes
        if (file.exists() && file.length() > 0) {
            boolean truncated = file.delete();
            if (!truncated) {
                throw new IOException("Failed to truncate the file.");
            }
            file.createNewFile(); // Recreate empty file after truncation
        }

        // O_WRONLY flag simulation: Open file for writing only
        try (java.io.FileWriter fileWriter = new java.io.FileWriter(file, false)) {
            System.out.println("File is open and ready for writing.");
        } catch (IOException e) {
            throw new IOException("Failed to write to the file.", e);
        }
    }
}