import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionExample {
    public static void main(String[] args) {
        try {
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            Path pathToFile = Paths.get("secret.txt");
            Files.write(pathToFile, content.getBytes());
            Files.setPosixFilePermissions(pathToFile, new java.util.HashSet<>(java.nio.file.attribute.PosixFilePermissions.fromString("rw-------")));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}