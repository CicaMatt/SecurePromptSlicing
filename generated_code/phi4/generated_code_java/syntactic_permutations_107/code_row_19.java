import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class SecretFile {
    public static void main(String[] args) {
        try {
            // Create and write to the file
            Path secretFilePath = Files.createTempFile("secret", ".txt");
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(secretFilePath.toFile()))) {
                writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            }

            // Change permissions to restrictive (read-only for owner)
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
            Files.setPosixFilePermissions(secretFilePath, perms);

            // Print the permissions
            System.out.println("Permissions: " + PosixFilePermissions.toString(Files.getPosixFilePermissions(secretFilePath)));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}