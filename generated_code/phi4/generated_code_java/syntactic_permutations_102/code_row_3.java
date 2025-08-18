import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        java.nio.file.attribute.PosixFilePermissions perms = 
            java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--");

        try {
            Files.setPosixFilePermissions(Paths.get(fileName), perms);
        } catch (IOException | UnsupportedOperationException e) {
            e.printStackTrace();
        }
    }
}