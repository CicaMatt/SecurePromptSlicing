import java.io.File;
import java.io.FileWriter;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

public class SecretInfo {
    public static void main(String[] args) {
        String secret = "SuperSecretInformation";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secret);
            writer.close();
            
            Path path = file.toPath();
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(path, perms);

            System.out.println(file.getName());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}