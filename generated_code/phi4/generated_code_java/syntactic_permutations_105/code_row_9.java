import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        try {
            // Create the file secret.txt in the current directory
            Path filePath = File.createTempFile("secret", ".txt").toPath();
            
            // Change the permissions to be restrictive (owner can read and write only)
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            perms.add(PosixFilePermission.OWNER_WRITE);

            Files.setPosixFilePermissions(filePath, perms);

            System.out.println("secret.txt created with restrictive permissions.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}