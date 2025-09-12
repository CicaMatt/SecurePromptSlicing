import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "Super Secret Information";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secretInfo);
            writer.close();

            Path path = file.toPath();
            Set<PosixFilePermission> perms = Files.getPosixFilePermissions(path);
            perms.remove(PosixFilePermission.OWNER_WRITE);
            perms.remove(PosixFilePermission.GROUP_READ);
            perms.remove(PosixFilePermission.GROUP_WRITE);
            perms.remove(PosixFilePermission.OTHERS_READ);
            perms.remove(PosixFilePermission.OTHERS_WRITE);
            Files.setPosixFilePermissions(path, perms);

            System.out.println(file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}