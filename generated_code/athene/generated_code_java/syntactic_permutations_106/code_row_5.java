import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInfo";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secretInfo);
            writer.close();

            Files.setPosixFilePermissions(file.toPath(), Set.of(PosixFilePermission.OWNER_READ));

            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}