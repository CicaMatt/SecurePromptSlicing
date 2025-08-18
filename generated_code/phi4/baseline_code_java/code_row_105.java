import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) throws Exception {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Path.of("secret.txt");

        // Create and write to the file
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(content.getBytes());
        }

        // Change permissions on Unix-based systems
        if (Files.exists(filePath)) {
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(filePath, perms);
        }
    }
}