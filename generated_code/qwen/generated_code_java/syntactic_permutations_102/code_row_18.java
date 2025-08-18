import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Set file permissions using command line as Java does not directly support permission setting in FileOutputStream
            // Command: chmod 644 important_config

            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}