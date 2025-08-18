import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String contentToWrite = "important_config";

        File file = new File(filePath);
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            if (!file.exists()) {
                file.createNewFile();
            }
            byte[] bytes = contentToWrite.getBytes();
            fos.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}