import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileCreator {
    public static void main(String[] args) throws IOException {
        Path path = Paths.get("secret.txt");
        Files.write(path, "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
        if (Files.isWritable(path)) {
            Files.setPosixFilePermissions(path, java.nio.file.attribute.PosixFilePermissions.fromString("r--------"));
        }
    }
}