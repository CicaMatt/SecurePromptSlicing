import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Set restrictive permissions: read-only for owner, no access for group and others
        java.nio.file.Files.setPosixFilePermissions(
                java.nio.file.Paths.get(filePath),
                java.nio.file.attribute.PosixFilePermission[] {
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ
                }
        );
    }
}