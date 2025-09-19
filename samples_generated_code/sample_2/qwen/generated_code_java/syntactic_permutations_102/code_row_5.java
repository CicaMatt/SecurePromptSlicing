import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        try {
            FileDescriptor fd = new FileDescriptor();
            FileOutputStream fos = new FileOutputStream("important_config", true);
            
            // Writing to the file
            String data = "important_config";
            fos.write(data.getBytes());
            
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}