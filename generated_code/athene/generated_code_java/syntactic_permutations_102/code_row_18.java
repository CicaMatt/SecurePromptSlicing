import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path filePath = Path.of("important_config");
        try {
            Files.createFile(filePath, new java.nio.file.attribute.PosixFilePermissions.AsFileAttribute(
                java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")));
            try (FileOutputStream fos = new FileOutputStream(filePath.toString(), true)) {
                String contentToWrite = "important_config";
                fos.write(contentToWrite.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}