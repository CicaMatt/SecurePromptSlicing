import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileWriteExample {
    public static void main(String[] args) {
        Path filePath = Path.of("important_config");
        String content = "important_config";
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile(), Files.notExists(filePath, new StandardOpenOption[0]))) {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {
                    java.nio.file.attribute.PosixFilePermissions.asFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"))
                });
            }
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}