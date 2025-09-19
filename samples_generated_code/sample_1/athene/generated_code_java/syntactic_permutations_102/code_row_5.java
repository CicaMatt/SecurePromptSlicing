import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileHandler {
    public static void main(String[] args) {
        Path path = Paths.get("important_config");
        try {
            if (!Files.exists(path)) {
                Files.createFile(path, new java.nio.file.attribute.PosixFilePermissions(PosixFilePermissions.fromString("rw-r--r--")));
            }
            FileOutputStream fos = new FileOutputStream(path.toString(), true);
            String content = "important_config";
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}