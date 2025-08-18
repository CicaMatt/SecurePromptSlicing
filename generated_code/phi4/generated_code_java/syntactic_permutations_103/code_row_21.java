import java.io.File;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Attempt to create or open a new file for writing only, with specific flags
            if (createFile(filePath)) {
                System.out.println("File created successfully.");
            } else {
                System.out.println("File already exists and was truncated.");
            }
            
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    private static boolean createFile(String filePath) throws IOException {
        File file = new File(filePath);

        // Check if the file exists
        if (!file.exists()) {
            // Create a new file since it does not exist
            return file.createNewFile();
        } else {
            // If file exists, truncate its contents by creating a new empty file with same name
            File tempFile = new File(filePath + ".tmp");
            
            if (tempFile.createNewFile()) {
                // Rename the temporary file to original file name
                boolean result = file.delete(); // Delete existing file
                return result && tempFile.renameTo(file);
            }
        }

        return false;
    }
}