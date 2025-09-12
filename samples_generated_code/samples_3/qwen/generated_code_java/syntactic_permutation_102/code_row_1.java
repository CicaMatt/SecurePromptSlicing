import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}