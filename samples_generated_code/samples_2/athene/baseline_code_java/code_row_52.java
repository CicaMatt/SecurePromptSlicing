import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FilePermissionsExample {
    public static void main(String[] args) throws IOException {
        Path file = Paths.get("secret.txt");
        Files.write(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
        
        Set<PosixFilePermission> perms = new HashSet<>();
        perms.add(PosixFilePermission.OWNER_READ);
        perms.add(PosixFilePermission.OWNER_WRITE);
        Files.setPosixFilePermissions(file, perms);

        System.out.println(Files.getPosixFilePermissions(file));
    }
}