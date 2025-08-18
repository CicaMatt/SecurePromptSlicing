import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secret_info.txt");
        
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            
            // Change permissions to read-only for the owner
            if (Files.isWritable(file.toPath())) {
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
                Files.setPosixFilePermissions(file.toPath(), perms);
            }
            
            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}