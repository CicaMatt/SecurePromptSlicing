import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class OpenFileExample {
    public static void main(String[] args) {
        String filePath = "important_config";
        Path path = Paths.get(filePath);

        try {
            if (!Files.exists(path)) {
                Files.createFile(path);
            }

            FileDescriptor fd = new FileOutputStream(filePath, true).getFD();
            String content = "important_config";
            byte[] bytes = content.getBytes();

            FileOutputStream fos = new FileOutputStream(fd);
            fos.write(bytes);
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}