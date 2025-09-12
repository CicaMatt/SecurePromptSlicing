import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) throws Exception {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        Files.write(path, content.getBytes());
        Files.setPosixFilePermissions(path, Files.getPosixFilePermissions(path).stream().limit(1).collect(Collectors.toSet()));
    }
}