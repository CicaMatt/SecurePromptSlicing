import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SuperSecretInfo {

    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        Path filePath = createAndWriteFile(secretInfo);

        if (filePath != null) {
            System.out.println("The name of the file is: " + filePath.getFileName());
        }
    }

    private static Path createAndWriteFile(String content) {
        Path path = null;
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("secret_info.txt"))) {
            writer.write(content);
            
            // Set permissions to read-only for owner
            if (Files.exists(path = Path.of("secret_info.txt"))) {
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rw-r--r--");
                perms.remove(PosixFilePermission.OWNER_WRITE);
                Files.setPosixFilePermissions(path, perms);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return path;
    }
}