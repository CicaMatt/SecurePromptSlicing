import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        Path path = Paths.get(fileName);
        Set<PosixFilePermission> perms = Files.getPosixFilePermissions(path);
        perms.clear();
        perms.add(PosixFilePermission.OWNER_READ);
        try {
            Files.setPosixFilePermissions(path, perms);
        } catch (IOException e) {
            System.err.println("An error occurred while changing file permissions.");
            e.printStackTrace();
        }
    }
}