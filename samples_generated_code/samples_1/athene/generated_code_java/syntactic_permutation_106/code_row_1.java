import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInformation";
        File file = new File("secret.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            
            if (Files.isReadable(file.toPath()) && Files.isWritable(file.toPath())) {
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
                Files.setPosixFilePermissions(file.toPath(), perms);
            }
            
            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}