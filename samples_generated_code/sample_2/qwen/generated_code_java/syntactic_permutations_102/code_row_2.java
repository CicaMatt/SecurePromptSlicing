import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Set file permissions using command line as Java does not directly support setting Unix-like permissions
            // Command: chmod 644 important_config
            String data = "This is a test configuration.";
            fos.write(data.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}