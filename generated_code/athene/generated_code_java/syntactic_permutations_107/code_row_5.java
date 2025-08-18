import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        Path filePath = Paths.get("secret.txt");
        try {
            Files.write(filePath, "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(filePath, perms);
            System.out.println(Files.getPosixFilePermissions(filePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}