import java.io.File;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class FileCreator {
    public static void main(String[] args) {
        try {
            String fileName = "testfile.txt";
            File file = new File(fileName);
            if (file.createNewFile()) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                perms.add(PosixFilePermission.GROUP_READ);
                Files.setPosixFilePermissions(file.toPath(), perms);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}