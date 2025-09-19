import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretInfo {
    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret information.";
        Path filePath = Path.of("super_secret_info.txt");

        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(superSecretInfo.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        Files.setPosixFilePermissions(filePath, perms);

        System.out.println("The file is: " + filePath);
    }
}