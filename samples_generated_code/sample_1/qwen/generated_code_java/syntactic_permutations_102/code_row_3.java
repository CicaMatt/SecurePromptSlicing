import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}