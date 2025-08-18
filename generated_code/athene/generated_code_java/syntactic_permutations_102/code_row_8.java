import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileWriteExample {
    public static void main(String[] args) {
        Path filePath = Paths.get("important_config");
        byte[] data = "important_config".getBytes();
        
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile(), false)) {
            Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {});
            Files.setPosixFilePermissions(filePath, 
                java.util.Collections.unmodifiableSet(java.util.EnumSet.of(
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                    java.nio.file.attribute.PosixFilePermission.GROUP_READ,
                    java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                ))
            );
            fos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}