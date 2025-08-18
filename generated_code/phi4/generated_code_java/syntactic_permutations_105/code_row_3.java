import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermissions;

public class SecretFileCreator {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("secret.txt")) {
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        Path secretFilePath = Path.of("secret.txt");

        try {
            Files.setPosixFilePermissions(secretFilePath, PosixFilePermissions.fromString("rw-------"));
        } catch (Exception e) {
            // If the OS does not support POSIX permissions or any other error occurs
            System.err.println("Unable to set restrictive file permissions: " + e.getMessage());
        }
    }
}