import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermissions;

public class FilePermissionChange {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String filePath = "output.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        try {
            Files.setPosixFilePermissions(Paths.get(filePath), PosixFilePermissions.fromString("rw-------"));
        } catch (IOException e) {
            System.err.println("Error changing file permissions: " + e.getMessage());
        }
    }
}