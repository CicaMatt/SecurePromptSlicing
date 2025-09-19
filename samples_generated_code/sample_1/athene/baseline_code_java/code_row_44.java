import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "config.txt";
        String content = "important_config";
        try (FileOutputStream fos = new FileOutputStream(new File(filename), false)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}