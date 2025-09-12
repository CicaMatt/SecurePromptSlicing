import java.nio.file.*;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) {
        Path path = Paths.get("secret.txt");
        try {
            Files.write(path, "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            perms.add(PosixFilePermission.OWNER_WRITE);
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}