import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
            Files.setPosixFilePermissions(path, java.util.Collections.singleton(java.nio.file.attribute.PosixFilePermission.OWNER_READ));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}