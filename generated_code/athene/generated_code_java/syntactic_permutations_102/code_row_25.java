import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        Path path = Paths.get(filePath);
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.PosixFilePermission[]{
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                    java.nio.file.attribute.PosixFilePermission.GROUP_READ,
                    java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                });
            }
            try (FileOutputStream fos = new FileOutputStream(filePath)) {
                String content = "important_config";
                fos.write(content.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}