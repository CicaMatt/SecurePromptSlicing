import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            byte[] bytesToWrite = content.getBytes();
            fos.write(bytesToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}