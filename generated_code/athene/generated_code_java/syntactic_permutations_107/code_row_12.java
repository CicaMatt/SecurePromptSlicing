import java.io.File;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileHandler {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        Path path = Paths.get("secret.txt");
        
        try (FileOutputStream fos = new FileOutputStream(path.toFile())) {
            fos.write(content.getBytes());
            
            // Change file permissions to restrictive (read-write for owner only)
            Files.setPosixFilePermissions(path, 
                java.util.Set.of(
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE
                )
            );

            // Print file path
            System.out.println("File created at: " + path.toAbsolutePath());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}