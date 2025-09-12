import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermissions;

public class SecretFileCreator {

    public static void main(String[] args) {
        try {
            String filePath = "secret.txt";
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

            // Write the string to secret.txt
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
                writer.write(content);
            }

            // Change permissions of the file to be restrictive (read and write for owner only)
            Path path = Path.of(filePath);
            if (!Files.exists(path.getParent())) {
                Files.createDirectories(path.getParent());
            }
            
            Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rw-------"));

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}