import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        
        try {
            // Open the file for reading and writing, creating it if it doesn't exist
            Files.write(filePath, "important_config".getBytes(), 
                StandardOpenOption.CREATE, 
                StandardOpenOption.TRUNCATE_EXISTING, 
                StandardOpenOption.WRITE);
            
            // Set permissions: read/write for owner, read-only for group and others
            Files.setPosixFilePermissions(
                filePath,
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
            );
            
            System.out.println("File 'important_config' created and written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}