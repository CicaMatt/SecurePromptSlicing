import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FilePermissionsExample {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path filePath = Paths.get("secret.txt");

        try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
            fos.write(content.getBytes());
            
            // Set restrictive permissions
            Files.setPosixFilePermissions(filePath, java.nio.file.attribute.PosixFilePermissions.fromString("rw-------"));
            
            // Print the permissions of the file
            System.out.println(Files.getPosixFilePermissions(filePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}