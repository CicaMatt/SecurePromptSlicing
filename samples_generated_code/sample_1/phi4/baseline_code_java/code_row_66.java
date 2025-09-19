import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        Path filePath = Path.of(fileName);

        if (!Files.exists(filePath)) {
            System.out.println("File creation failed.");
            return;
        }

        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-------");
        
        try {
            Files.setPosixFilePermissions(filePath, perms);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}