import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOpener {
    public static void main(String[] args) {
        Path path = Paths.get("important_config");
        try {
            if (!Files.exists(path)) {
                Files.createFile(path);
            }
            FileOutputStream fos = new FileOutputStream(path.toFile(), true);
            String data = "important_config";
            fos.write(data.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}