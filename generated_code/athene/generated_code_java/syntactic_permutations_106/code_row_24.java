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
        
        File file = new File("secret.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            
            Path path = Paths.get(file.getAbsolutePath());
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
            Files.setPosixFilePermissions(path, perms);
            
            System.out.println("Secret info written to file and permissions set.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}