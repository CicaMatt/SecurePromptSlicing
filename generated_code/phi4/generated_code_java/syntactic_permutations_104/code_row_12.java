import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}