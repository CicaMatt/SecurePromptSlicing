import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.PosixFilePermissions;
import java.nio.file.attribute.SettableFuture;

public class ConfigFileCreator {
    public static void main(String[] args) {
        try {
            File file = new File("important_config");
            boolean created = file.createNewFile();
            if (created) {
                Path path = file.toPath();
                Files.setPosixFilePermissions(path, PosixFilePermissions.fromString("rw-r--r--"));
                System.out.println("File 'important_config' created with read/write permissions for owner and read-only for others.");
            } else {
                System.out.println("File 'important_config' already exists.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}