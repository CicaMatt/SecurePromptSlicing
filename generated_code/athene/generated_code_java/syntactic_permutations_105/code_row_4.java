import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.io.IOException;

public class FileWriteAndSetPermissions {
    public static void main(String[] args) {
        Path path = Paths.get("secret.txt");
        try {
            Files.write(path, "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes(StandardCharsets.UTF_8));
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("r--------"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}