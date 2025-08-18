import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.Files;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            System.out.println("File name: " + file.getName());

            if (Files.isWritable(file.toPath())) {
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
                Files.setPosixFilePermissions(file.toPath(), perms);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}