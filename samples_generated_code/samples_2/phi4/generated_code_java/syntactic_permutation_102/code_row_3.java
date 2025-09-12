import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.nio.charset.StandardCharsets;

public class ImportantConfig {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config\n";

        try {
            // Open the file with read and write permissions, create if it doesn't exist
            Files.write(Paths.get(filePath), content.getBytes(StandardCharsets.UTF_8),
                    StandardOpenOption.CREATE, StandardOpenOption.WRITE);

            FileOutputStream fos = new FileOutputStream(filePath, true);
            
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}