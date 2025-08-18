import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String superSecretInfo = "This is a super secret message!";
        try {
            Path filePath = Files.createTempFile("secret", ".txt");
            try (FileWriter writer = new FileWriter(filePath.toFile())) {
                writer.write(superSecretInfo);
            }
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(filePath, perms);

            System.out.println("File created: " + filePath.getFileName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}