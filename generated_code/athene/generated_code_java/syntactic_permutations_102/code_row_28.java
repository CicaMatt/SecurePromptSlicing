import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        Path path = Paths.get(filename);
        int flags = Files.exists(path) ? 0 : StandardOpenOption.CREATE.toMask() | 
            StandardOpenOption.READ.toMask() | StandardOpenOption.WRITE.toMask();
        
        try (FileOutputStream fos = new FileOutputStream(filename, false)) {
            if ((flags & StandardOpenOption.CREATE.toMask()) != 0 && !Files.exists(path)) {
                Files.setPosixFilePermissions(path, 
                    java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--"));
            }
            String content = "important_config";
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}