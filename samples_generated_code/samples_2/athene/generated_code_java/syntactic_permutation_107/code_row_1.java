import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FilePermissionExample {
    public static void main(String[] args) {
        Path path = Paths.get("secret.txt");
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
            
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(path, perms);
            
            System.out.println(Files.getPosixFilePermissions(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}