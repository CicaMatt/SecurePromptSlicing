import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String contentToWrite = ".";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] bytes = contentToWrite.getBytes();
            fos.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}