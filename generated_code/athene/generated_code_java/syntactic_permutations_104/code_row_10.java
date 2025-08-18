import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "config.txt";
        byte[] content = "important_config".getBytes();
        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            fos.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}