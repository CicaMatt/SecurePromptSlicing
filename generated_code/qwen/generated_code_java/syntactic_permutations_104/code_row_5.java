import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "config.txt";
        String content = "important_config";

        try {
            FileOutputStream fos = new FileOutputStream(filePath, true);
            FileDescriptor fd = fos.getFD();
            
            if (!new File(filePath).exists()) {
                new java.io.File(filePath).createNewFile();
            }

            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}