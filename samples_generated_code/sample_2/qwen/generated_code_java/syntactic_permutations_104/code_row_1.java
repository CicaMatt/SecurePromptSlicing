import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String contentToWrite = "important_config";

        try {
            FileOutputStream fileOutputStream = new FileOutputStream(filePath, true);
            fileOutputStream.write(contentToWrite.getBytes());
            fileOutputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}