import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenWriteExample {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            // Check if the file was created
            FileDescriptor fd = fos.getFD();
            if (fd.valid()) {
                byte[] bytes = contentToWrite.getBytes();
                fos.write(bytes);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}