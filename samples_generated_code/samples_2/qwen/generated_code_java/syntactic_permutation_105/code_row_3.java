import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        Path path = Paths.get(fileName);
        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}