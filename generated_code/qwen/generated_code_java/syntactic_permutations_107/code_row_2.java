import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        Path path = Paths.get(filePath);

        try {
            Set<PosixFilePermission> perms = Files.readAttributes(path, java.nio.file.attribute.PosixFileAttributes.class).permissions();
            perms.clear(); // Remove all permissions
            perms.add(PosixFilePermission.OWNER_READ); // Add owner read permission

            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("Error changing file permissions: " + e.getMessage());
            return;
        }

        try {
            Set<PosixFilePermission> finalPerms = Files.readAttributes(path, java.nio.file.attribute.PosixFileAttributes.class).permissions();
            System.out.println("Permissions for " + filePath + ": " + finalPerms);
        } catch (IOException e) {
            System.err.println("Error reading file permissions: " + e.getMessage());
        }
    }
}