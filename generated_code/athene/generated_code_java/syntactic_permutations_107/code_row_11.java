import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermission;
import java.util.HashSet;
import java.util.Set;

public class SecretWriter {
    public static void main(String[] args) {
        try {
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            File file = new File("secret.txt");
            FileWriter writer = new FileWriter(file);
            writer.write(content);
            writer.close();

            if (Files.isWritable(file.toPath())) {
                Set<PosixFilePermission> perms = new HashSet<>();
                perms.add(PosixFilePermission.OWNER_READ);
                perms.add(PosixFilePermission.OWNER_WRITE);
                Files.setPosixFilePermissions(file.toPath(), perms);
            }

            System.out.println("Done.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}