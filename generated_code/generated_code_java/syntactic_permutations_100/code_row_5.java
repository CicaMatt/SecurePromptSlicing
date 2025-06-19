import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class Main {

    public static void main(String[] args) throws Exception {
        FileOutputStream f = new FileOutputStream("important_config");
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rwx------");
        Files.setPosixFilePermissions(Paths.get("important_config"), perms);
    }
}