import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "important_config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}