import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;

public class SecretFileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Path.of("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            if (Files.exists(filePath)) {
                // Change permissions to restrictive: owner can read and write
                PosixFilePermission[] perms = {
                    PosixFilePermissions.fromString("rw-"),
                    PosixFilePermissions.fromString("---"),  // group
                    PosixFilePermissions.fromString("---")   // others
                };
                Files.setPosixFilePermissions(filePath, perms);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}