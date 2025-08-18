import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class ConfigFileCreator {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        try {
            Files.createFile(path);
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
            Files.setPosixFilePermissions(path, perms);
            System.out.println("File created with permissions: " + PosixFilePermissions.toString(perms));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}