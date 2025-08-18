import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = ".important_config";
        String content = "important_config";

        try {
            FileOutputStream fos = new FileOutputStream(fileName, true);
            FileDescriptor fd = fos.getFD();
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}