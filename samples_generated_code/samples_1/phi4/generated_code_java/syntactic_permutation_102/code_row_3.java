import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "This is some important configuration data.";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] bytesToWrite = content.getBytes();
            fos.write(bytesToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}