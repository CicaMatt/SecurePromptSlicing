import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("secret.txt")) {
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            fos.write(content.getBytes());
            Path path = Paths.get("secret.txt");
            Files.setPosixFilePermissions(path, Files.getPosixFilePermissions(path).stream()
                    .filter(p -> p.name().equals("OWNER_READ"))
                    .toArray(java.nio.file.attribute.PosixFilePermission[]::new));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}