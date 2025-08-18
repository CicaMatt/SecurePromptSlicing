import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
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

        // Change permissions to restrictive: owner can read and write, others have no permissions
        if (file.setReadable(true, false)) {
            System.out.println("Read permission granted for owner.");
        }
        if (file.setWritable(true, false)) {
            System.out.println("Write permission granted for owner.");
        }

        // Remove all other permissions
        try {
            Files.setPosixFilePermissions(file.toPath(), PosixFilePermission.NONE);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Print the current file permissions
        if (file.canRead()) {
            System.out.println("Owner has read permission.");
        }
        if (file.canWrite()) {
            System.out.println("Owner has write permission.");
        }
        if (!file.canExecute()) {
            System.out.println("No execute permission for owner or others.");
        }

        try {
            Set<PosixFilePermission> permissions = Files.getPosixFilePermissions(file.toPath());
            System.out.println("Current file permissions: " + permissions);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}