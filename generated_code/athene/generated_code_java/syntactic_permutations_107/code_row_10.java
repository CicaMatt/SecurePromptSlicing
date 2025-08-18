import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        Path file = Paths.get("secret.txt");
        try {
            Files.write(file, "This is a secret message.".getBytes());
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(file, perms);
            System.out.println("File permissions: " + Files.getPosixFilePermissions(file));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}