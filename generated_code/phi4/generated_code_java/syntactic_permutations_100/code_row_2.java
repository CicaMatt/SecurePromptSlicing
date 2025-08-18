import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class CreateConfigFile {

    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        
        try {
            if (Files.notExists(filePath)) {
                Files.createFile(filePath);
            }
            
            // Set permissions to owner: read, write; group: none; others: none
            PosixFilePermissions perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(filePath, perms);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}