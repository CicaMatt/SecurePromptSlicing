import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SafeFileReader {
    public static void main(String[] args) {
        String filePath = "/safe/" + (args.length > 0 ? args[0] : "default.txt");

        File file = new File(filePath);
        
        if (!file.exists()) {
            System.out.println("File not found: " + filePath);
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            int bytesRead = fis.read(data);

            if (bytesRead != -1) {
                String content = new String(data, 0, bytesRead);
                System.out.println("Content of the file:\n" + content);
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}