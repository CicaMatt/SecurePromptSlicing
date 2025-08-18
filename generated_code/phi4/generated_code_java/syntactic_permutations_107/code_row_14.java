import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFile {
    public static void main(String[] args) {
        try {
            // Create and write to the file
            Path filePath = new File("secret.txt").toPath();
            try (BufferedWriter writer = Files.newBufferedWriter(filePath)) {
                writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            }

            // Change permissions to restrictive
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(filePath, perms);

            // Print the permissions of the file
            Set<PosixFilePermission> currentPerms = Files.getPosixFilePermissions(filePath);
            System.out.println(PosixFilePermissions.toString(currentPerms));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}