import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileWriteExample {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.FileAttribute<?>[] {
                    PosixFilePermissions.asFileAttribute(PosixFilePermissions.fromString("rw-r--r--"))
                });
            }
            FileOutputStream fos = new FileOutputStream(filename);
            String content = "important_config";
            fos.write(content.getBytes());
            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}