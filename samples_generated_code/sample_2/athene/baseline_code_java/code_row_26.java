import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FileCreator {
    public static void main(String[] args) {
        Path filePath = new File("important_config").toPath();
        try {
            Files.createFile(filePath);
            if (Files.isReadable(filePath)) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                perms.add(PosixFilePermission.GROUP_READ);
                Files.setPosixFilePermissions(filePath, perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}