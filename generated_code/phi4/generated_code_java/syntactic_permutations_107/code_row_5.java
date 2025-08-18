import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Paths.get("secret_file.txt");

        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        // Change the permissions to restrictive (read and write for owner only)
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(filePath, perms);
        } catch (IOException e) {
            System.err.println("Error setting file permissions: " + e.getMessage());
        }

        // Print the current file permissions
        try {
            Set<PosixFilePermission> currentPerms = Files.getPosixFilePermissions(filePath);
            String permString = PosixFilePermissions.toString(currentPerms);
            System.out.println("Current file permissions: " + permString);
        } catch (IOException e) {
            System.err.println("Error getting file permissions: " + e.getMessage());
        }
    }
}