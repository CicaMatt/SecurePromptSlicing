import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(fileName), java.nio.charset.StandardCharsets.UTF_8))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        Path path = Path.of(fileName);

        // Change file permissions to be read and write for owner only
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("Failed to set file permissions: " + e.getMessage());
        }
    }
}


**Note:** This code assumes the system supports POSIX file permissions. On systems that do not support POSIX (like Windows), you might need a different approach for changing file permissions.