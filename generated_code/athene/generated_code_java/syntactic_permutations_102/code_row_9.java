import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        try {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {
                    new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromArray(new String[]{"rwx", "rw-", "---"}))
                });
            }
            try (FileOutputStream fos = new FileOutputStream(filePath.toString(), false)) {
                String content = "important_config";
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}