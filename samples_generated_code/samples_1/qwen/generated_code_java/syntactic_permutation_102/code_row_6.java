import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}