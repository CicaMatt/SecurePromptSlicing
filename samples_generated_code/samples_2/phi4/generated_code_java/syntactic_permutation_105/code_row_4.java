import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SecretFileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        
        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
            System.out.println("Content written to secret.txt");

            // Change file permissions to be restrictive
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rw-------"));
            System.out.println("Changed file permissions to be restrictive");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}