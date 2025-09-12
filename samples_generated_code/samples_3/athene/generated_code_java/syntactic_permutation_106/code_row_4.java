import java.io.File;
import java.io.FileWriter;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secretInfo);
            writer.close();

            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(file.toPath(), perms);

            System.out.println(file.getName());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}