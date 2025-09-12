import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "config.txt";
        String dataToWrite = "important_config";

        try {
            File file = new File(filePath);
            FileOutputStream fos = new FileOutputStream(file, true); // O_RDWR and O_CREAT equivalent in Java

            byte[] bytes = dataToWrite.getBytes();
            fos.write(bytes);

            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}