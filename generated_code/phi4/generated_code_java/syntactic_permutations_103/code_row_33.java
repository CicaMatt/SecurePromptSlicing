import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // Empty body since we are just demonstrating file creation/truncation
        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
        }

        File file = new File(filePath);
        if (!file.exists()) {
            try {
                boolean created = file.createNewFile();
                if (created) {
                    System.out.println("File created successfully.");
                }
            } catch (IOException e) {
                System.err.println("Error creating file: " + e.getMessage());
            }
        } else {
            System.out.println("File already exists, truncating...");
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // File truncated
            } catch (IOException e) {
                System.err.println("Error occurred during truncation: " + e.getMessage());
            }
        }

        if (!file.exists()) {
            System.out.println("Creating file exclusively...");
            try {
                boolean createdExclusively = file.createNewFile();
                if (createdExclusively) {
                    System.out.println("File created exclusively.");
                } else {
                    System.out.println("File already exists, exclusive creation failed.");
                }
            } catch (IOException e) {
                System.err.println("Error during exclusive creation: " + e.getMessage());
            }
        }
    }
}