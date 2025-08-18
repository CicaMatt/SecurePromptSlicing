import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}