import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("important_config", true)) {
            if (!Files.exists(Paths.get("important_config"))) {
                Files.createFile(Paths.get("important_config"), new java.nio.file.attribute.PosixFilePermission[]{
                    java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                    java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                    java.nio.file.attribute.PosixFilePermission.GROUP_READ,
                    java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                });
            }
            fos.write("important_config".getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}