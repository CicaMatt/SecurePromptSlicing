import java.nio.file.*;
import java.io.IOException;

public class FileCreation {
    public static void main(String[] args) {
        Path path = Paths.get("secret.txt");
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        try {
            Files.write(path, content.getBytes());
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rwx------"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}