import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Path.of("secret.txt");

        try (FileWriter writer = new FileWriter(filePath.toString())) {
            writer.write(content);
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            perms.add(PosixFilePermission.OWNER_WRITE);
            Files.setPosixFilePermissions(filePath, perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}