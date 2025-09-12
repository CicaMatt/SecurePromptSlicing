import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class SecretFileCreator {

    public static void main(String[] args) {
        String secretContent = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Path.of("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(secretContent.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }

        Set<PosixFilePermission> permissions = PosixFilePermissions.fromString("rw-------");
        try {
            Files.setPosixFilePermissions(filePath, permissions);
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            System.out.println(Files.getPosixFilePermissions(filePath));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}