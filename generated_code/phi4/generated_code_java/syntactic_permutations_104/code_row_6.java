import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "config.txt";
        String importantConfig = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] data = importantConfig.getBytes();
            fos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Alternatively using Files class
        try {
            Files.writeString(Paths.get(filePath), importantConfig, StandardOpenOption.CREATE, StandardOpenOption.WRITE);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}