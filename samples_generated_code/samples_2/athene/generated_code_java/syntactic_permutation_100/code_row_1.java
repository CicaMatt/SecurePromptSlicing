import java.io.File;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;
import java.util.HashSet;

public class ConfigCreator {
    public static void main(String[] args) {
        File config = new File("important_config");
        try {
            if (config.createNewFile()) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                perms.add(PosixFilePermission.GROUP_READ);
                Files.setPosixFilePermissions(config.toPath(), perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}