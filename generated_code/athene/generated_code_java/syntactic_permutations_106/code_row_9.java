import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "SuperSecretInformation";
        try {
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(secretInfo);
            writer.close();

            if (Files.isWritable(file.toPath())) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                Files.setPosixFilePermissions(file.toPath(), perms);
            }

            System.out.println("File name: " + file.getName());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}