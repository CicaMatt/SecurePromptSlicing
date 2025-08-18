import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class CreateConfigFile {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r-----");
        try {
            Files.createFile(path, PosixFilePermissions.asFileAttribute(perms));
            System.out.println("File created with permissions: " + PosixFilePermissions.toString(Files.getPosixFileAttributes(path).permissions()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}