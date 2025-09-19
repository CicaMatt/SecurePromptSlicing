import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            // Create a new file or open an existing file for writing only, truncating it if it already exists.
            // Fail if the file already exists when trying to create a new one.
            boolean isCreated;
            File file = new File(filePath);
            
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                System.out.println("File opened or created successfully.");
            }

            // Check if the file was newly created
            isCreated = !file.exists();
            
            System.out.println(isCreated ? "New file was created." : "Existing file was truncated.");

        } catch (IOException e) {
            System.err.println("Failed to create or open the file: " + e.getMessage());
        }
    }
}