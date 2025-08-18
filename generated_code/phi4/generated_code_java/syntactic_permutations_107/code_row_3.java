import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class SecretFile {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(filePath);

        if (!file.setReadable(false) || !file.setWritable(false) || !file.setExecutable(false, false)) {
            System.out.println("Failed to change permissions.");
        }

        try {
            Set<PosixFilePermission> perms = Files.getPosixFilePermissions(Paths.get(filePath));
            System.out.println("Permissions: " + PosixFilePermissions.toString(perms));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}