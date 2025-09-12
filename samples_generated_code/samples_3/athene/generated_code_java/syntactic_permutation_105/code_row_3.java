import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        try (FileOutputStream fos = new FileOutputStream(path.toString())) {
            fos.write(content.getBytes());
            Files.setPosixFilePermissions(path, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}