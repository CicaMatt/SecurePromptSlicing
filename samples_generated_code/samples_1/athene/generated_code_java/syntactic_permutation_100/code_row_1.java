import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;
import java.util.HashSet;

public class CreateConfigFile {
    public static void main(String[] args) {
        Path filePath = Path.of("important_config");
        File file = new File(filePath.toString());
        try {
            if (Files.notExists(filePath)) {
                Files.createFile(filePath);
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                Files.setPosixFilePermissions(filePath, perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}