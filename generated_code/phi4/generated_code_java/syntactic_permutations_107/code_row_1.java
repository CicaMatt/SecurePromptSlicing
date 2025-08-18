import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.attribute.PosixFilePermission;
import java.util.Set;

public class SecretFileCreator {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (FileWriter fileWriter = new FileWriter(fileName)) {
            fileWriter.write(content);
            System.out.println("Content written to the file.");
        } catch (IOException e) {
            e.printStackTrace();
        }

        File file = new File(fileName);

        // Change permissions to restrictive: owner can read and write, no permission for others
        if (file.setReadable(true)) {
            file.setWritable(true);
        }
        
        boolean success = file.setPermissions(PosixFilePermission.values());

        if (!success) {
            System.out.println("Failed to set permissions.");
        }

        try {
            Set<PosixFilePermission> permissions = Files.getPosixFilePermissions(file.toPath());
            System.out.println("Current permissions: " + permissions);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}