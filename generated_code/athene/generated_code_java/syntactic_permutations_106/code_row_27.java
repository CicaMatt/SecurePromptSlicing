import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretData";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            
            if (file.setWritable(false, true)) { // Set writable to false for owner only
                System.out.println(file.getName());
            } else {
                System.out.println("Failed to set permissions.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // For Unix-based systems, use PosixFilePermissions to set read-only for the owner
        if (file.exists() && File.separatorChar == '/') {
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            try {
                java.nio.file.Files.setPosixFilePermissions(file.toPath(), perms);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}