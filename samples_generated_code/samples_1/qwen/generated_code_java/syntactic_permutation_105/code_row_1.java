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
        }

        Path path = Paths.get(filePath);
        Set<PosixFilePermission> perms = Set.of(
                PosixFilePermission.OWNER_READ,
                PosixFilePermission.OWNER_WRITE
        );

        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("Error setting file permissions: " + e.getMessage());
        }
    }
}