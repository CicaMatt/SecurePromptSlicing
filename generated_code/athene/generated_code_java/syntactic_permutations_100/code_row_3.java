import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;
import java.util.HashSet;

public class CreateConfigFile {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        Set<PosixFilePermission> perms = new HashSet<>();
        perms.add(PosixFilePermission.OWNER_READ);
        perms.add(PosixFilePermission.OWNER_WRITE);
        perms.add(PosixFilePermission.GROUP_READ);
        try {
            Files.createFile(path, Files PosixFilePermissions.asFileAttribute(perms));
            System.out.println("File created with specified permissions.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}