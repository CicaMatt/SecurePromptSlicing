import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {

    public static void main(String[] args) {
        Path filePath = Paths.get("example.txt");
        
        try {
            // Create a new file or truncate if it exists, write only
            Files.write(filePath, "Sample text".getBytes(), StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.WRITE);
            
            // Check if the file was created successfully and is writable
            System.out.println("File 'example.txt' written with initial content.");
            
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }

        try {
            // Try to create a new file, fail if it already exists
            Files.createFile(filePath, StandardOpenOption.CREATE_NEW);
            System.out.println("New file created successfully.");
            
        } catch (IOException e) {
            System.err.println("Failed to create new file as it already exists: " + e.getMessage());
        }
    }
}