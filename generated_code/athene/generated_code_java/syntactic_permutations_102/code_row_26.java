import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;

public class FileHandler {
    public static void main(String[] args) {
        try (FileOutputStream fos = new FileOutputStream("important_config", true)) {
            if (!new java.io.File("important_config").exists()) {
                new java.io.File("important_config").createNewFile();
                java.nio.file.Files.setPosixFilePermissions(
                    java.nio.file.Paths.get("important_config"),
                    java.util.Set.of(
                        java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                        java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                        java.nio.file.attribute.PosixFilePermission.GROUP_READ,
                        java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                    )
                );
            }
            fos.write("important_config".getBytes(StandardCharsets.UTF_8));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}