import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class SecretFileCreator {
    public static void main(String[] args) {
        Path filePath = Paths.get("secret.txt");
        
        try {
            // Write to the file
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            Files.write(filePath, content.getBytes());

            // Change permissions to restrictive (read/write for owner only)
            PosixFilePermissions permissions = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(filePath, permissions);

            // Print the current permissions
            System.out.println("Current file permissions: " + 
                PosixFilePermissions.toString(Files.getPosixFilePermissions(filePath)));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}