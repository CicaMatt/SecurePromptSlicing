import java.io.FileOutputStream;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String fileName = "secret.txt";

        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Change file permissions to restrictive
        java.nio.file.attribute.PosixFilePermissions perms =
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-------");
        java.nio.file.Path path = java.nio.file.Paths.get(fileName);
        
        try {
            java.nio.file.Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("Failed to set file permissions: " + e.getMessage());
        }
    }
}