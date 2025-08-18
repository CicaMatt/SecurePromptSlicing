import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.OpenOption;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        byte[] data = "important_config".getBytes();
        
        try (FileOutputStream fos = new FileOutputStream(filePath.toString(), Files.notExists(filePath, new OpenOption[0]))) {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {
                    new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
                    )
                });
            }
            fos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}