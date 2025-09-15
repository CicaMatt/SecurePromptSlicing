import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class FileWithPermissions {
    public static void main(String[] args) {
        String fileName = "testfile.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change permissions to restrictive (read and write for owner only)
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(Paths.get(fileName), perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
