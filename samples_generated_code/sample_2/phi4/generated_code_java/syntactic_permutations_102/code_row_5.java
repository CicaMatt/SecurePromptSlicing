import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class ConfigFileHandler {
    public static void main(String[] args) {
        Path filePath = Path.of("important_config");
        String content = "important_config";

        try {
            // Open the file for reading and writing, creating it if necessary with appropriate permissions
            Files.write(filePath, content.getBytes(), StandardOpenOption.CREATE, StandardOpenOption.WRITE);

            // Set the file's permissions: read-write for owner, read-only for group and others
            java.nio.file.attribute.PosixFilePermissions.setPosixFilePermissions(
                filePath,
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
            );

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}