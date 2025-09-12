import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "config.txt";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}