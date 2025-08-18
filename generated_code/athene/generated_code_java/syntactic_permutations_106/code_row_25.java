import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Set;

public class SecretFileManager {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretPassword123";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);

            // Set read-only for the owner
            if (Files.isWritable(file.toPath())) {
                Path path = Paths.get(file.getAbsolutePath());
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                Files.setPosixFilePermissions(path, perms);
            }

            // Print file content to the screen
            System.out.println("File content:");
            System.out.println(new String(Files.readAllBytes(file.toPath())));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}