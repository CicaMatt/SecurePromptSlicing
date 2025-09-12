import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileWriteExample {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        String content = "important_config";
        try {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.PosixFilePermissions(PosixFilePermissions.fromString("rw-r--r--")));
            }
            try (FileOutputStream fos = new FileOutputStream(filePath.toString(), false)) {
                fos.write(content.getBytes());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}