import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try {
            // Ensure the file exists
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            }

            // Set permissions: owner read/write, group read, others read
            Files.setPosixFilePermissions(Paths.get(filePath), 
                java.nio.file.attribute.PosixFilePermission.fromString("rw-r--r--"));

            // Write content to the file
            try (FileOutputStream fos = new FileOutputStream(file)) {
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}