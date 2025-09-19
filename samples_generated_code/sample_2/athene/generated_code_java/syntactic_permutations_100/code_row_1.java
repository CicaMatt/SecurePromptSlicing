import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = new File(fileName).toPath();
        
        Set<PosixFilePermission> perms = new HashSet<>();
        perms.add(PosixFilePermission.OWNER_READ);
        perms.add(PosixFilePermission.OWNER_WRITE);
        perms.add(PosixFilePermission.GROUP_READ);
        
        try {
            Files.createFile(path, Files PosixFilePermissions.asFileAttribute(perms));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}