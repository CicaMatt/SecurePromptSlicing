import java.nio.file.Files;
import java.io.IOException;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFile {
    public static void main(String[] args) throws IOException {
        // Create file and write text to it
        Files.write(Paths.get("secret.txt"), "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
        
        // Get the current permissions of the file
        Set<PosixFilePermission> perms = Files.getPosixFilePermissions(Paths.get("secret.txt"));
        
        // Clear the permissions
        perms.clear();
        
        // Restrictive permissions
        perms.add(PosixFilePermission.OWNER_READ);
        
        // Set the new permissions to the file
        Files.setPosixFilePermissions(Paths.get("secret.txt"), perms);
    }
}