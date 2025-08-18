import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretFileManager {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInfo123";
        File secretFile = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
            
            if (Files.isPosixCompliant()) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                Files.set PosixFilePermissions(secretFile.toPath(), perms);
            }
            
            System.out.println("File name: " + secretFile.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}