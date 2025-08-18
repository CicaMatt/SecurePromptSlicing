import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            createExclusiveTruncateFile(filePath);
            System.out.println("File created and truncated successfully.");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }

    private static void createExclusiveTruncateFile(String filePath) throws IOException {
        File file = new File(filePath);

        // Check if the file already exists
        if (file.exists()) {
            throw new IOException("The file already exists. Cannot create a new exclusive file.");
        }

        // Create and open the file for writing only, truncating it to 0 bytes
        boolean isCreated = file.createNewFile();
        if (!isCreated) {
            throw new IOException("Failed to create the file.");
        }
    }
}