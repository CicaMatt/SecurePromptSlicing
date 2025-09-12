import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigFileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.FileAttribute<?>[] {
                    new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"))
                });
            }
            FileOutputStream fos = new FileOutputStream(filename);
            String content = "important_config";
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}