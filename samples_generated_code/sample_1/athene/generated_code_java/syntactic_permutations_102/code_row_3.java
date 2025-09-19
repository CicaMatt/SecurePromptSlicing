import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class FileWriteExample {
    public static void main(String[] args) {
        Path filePath = Path.of("important_config");
        byte[] content = "important_config".getBytes();
        
        try (FileOutputStream fos = new FileOutputStream(filePath.toFile(), Files.notExists(filePath, new StandardOpenOption[0]))) {
            if (!Files.exists(filePath)) {
                Files.createFile(filePath, new java.nio.file.attribute.FileAttribute<?>[] {});
                filePath.toFile().setReadable(true, false);
                filePath.toFile().setWritable(true, true);
                filePath.toFile().setExecutable(false, false);
            }
            fos.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}