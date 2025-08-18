import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        
        Path filePath = Paths.get("secret_info.txt");
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(secretInfo.getBytes());
            
            // Change permissions to read-only for the owner
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
            Files.setPosixFilePermissions(filePath, perms);
            
        } catch (IOException e) {
            System.err.println("I/O Error: " + e.getMessage());
        }

        System.out.println("File name: " + filePath.getFileName());
    }
}