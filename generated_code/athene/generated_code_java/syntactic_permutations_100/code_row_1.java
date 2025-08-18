import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FileCreator {
    public static void main(String[] args) {
        Path filePath = new File("important_config").toPath();
        try {
            if (Files.notExists(filePath)) {
                Files.createFile(filePath);
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
                Files.setPosixFilePermissions(filePath, perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}