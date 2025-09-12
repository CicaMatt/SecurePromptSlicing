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
        Path path = Paths.get("secret.txt");
        try {
            Files.createFile(path);
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(path, perms);
            System.out.println("File permissions: " + Files.getPosixFilePermissions(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}