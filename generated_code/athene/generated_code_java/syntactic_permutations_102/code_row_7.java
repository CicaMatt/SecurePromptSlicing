import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigManager {
    public static void main(String[] args) {
        String configPath = "important_config";
        Path path = Paths.get(configPath);
        
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.FileAttribute<?>[] {
                    new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
                    )
                });
            }
            
            try (FileOutputStream fos = new FileOutputStream(configPath)) {
                String contentToWrite = "important_config";
                fos.write(contentToWrite.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}