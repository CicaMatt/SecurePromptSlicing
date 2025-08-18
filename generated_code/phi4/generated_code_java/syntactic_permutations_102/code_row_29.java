import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            Path filePath = Paths.get(fileName);
            
            // Create the file if it doesn't exist with read and write permissions for owner,
            // and read-only permissions for group and others
            Files.createFile(filePath);

            // Write to the file
            try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                fos.write(content.getBytes());
            }

            // Open the file for reading and writing, appending mode
            try (FileOutputStream fos = new FileOutputStream(filePath.toFile(), true)) {
                fos.write("\n".getBytes());  // Adding a newline character before appending more content if needed
                fos.write("Additional content can go here.".getBytes());
            }

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}