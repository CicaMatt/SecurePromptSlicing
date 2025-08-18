import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "important_config";
        try {
            FileOutputStream fos = new FileOutputStream(filePath);
            String content = "important_config";
            fos.write(content.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}