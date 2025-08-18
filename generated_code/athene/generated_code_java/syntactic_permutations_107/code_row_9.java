import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;
import java.util.HashSet;

public class FilePermissions {
    public static void main(String[] args) {
        Path filePath = Path.of("secret.txt");
        try {
            Files.createFile(filePath);
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            perms.add(PosixFilePermission.OWNER_WRITE);
            Files.setPosixFilePermissions(filePath, perms);

            System.out.println(Files.getPosixFilePermissions(filePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}