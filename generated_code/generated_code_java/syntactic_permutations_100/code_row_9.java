import java.io.File;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.Files;
import java.util.Set;
 
public class CreateFileWithPermissions {
    public static void main(String[] args) {
        String filename = "test_file";
        
        File file = new File(filename);
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rwxr-x---");
        try {
            Files.createFile(file.toPath());
            Files.setPosixFilePermissions(file.toPath(), perms);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}