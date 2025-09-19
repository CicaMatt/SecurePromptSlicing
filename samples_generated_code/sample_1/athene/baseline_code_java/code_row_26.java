import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;
import java.util.HashSet;

public class ConfigFileCreator {
    public static void main(String[] args) {
        try {
            Path path = new File("important_config").toPath();
            if (Files.notExists(path)) {
                Files.createFile(path);
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                perms.add(PosixFilePermission.GROUP_READ);
                Files.setPosixFilePermissions(path, perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}