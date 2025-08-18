import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileExample {
    public static void main(String[] args) {
        String fileName = "important_config";
        String dataToWrite = "important_config";

        try {
            FileOutputStream fos = new FileOutputStream(fileName, true);
            FileDescriptor fd = fos.getFD();

            // Simulate O_CREAT and permission flags using Java
            if (!fd.valid()) {
                throw new IOException("File descriptor is not valid");
            }

            fos.write(dataToWrite.getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}