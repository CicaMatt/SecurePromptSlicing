import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            System.out.println(file.getAbsolutePath());

            if (Files.isPosixCompliant()) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                Files.setPosixFilePermissions(file.toPath(), perms);
            } else {
                file.setReadOnly();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}