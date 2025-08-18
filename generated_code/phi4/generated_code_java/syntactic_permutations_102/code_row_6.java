import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "Important configuration data";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}