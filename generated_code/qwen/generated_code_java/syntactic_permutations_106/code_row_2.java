import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret information!";
        String fileName = "secret.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
        try {
            Files.setPosixFilePermissions(Paths.get(fileName), perms);
        } catch (IOException e) {
            System.err.println("An error occurred while changing file permissions.");
            e.printStackTrace();
            return;
        }

        System.out.println(fileName);
    }
}