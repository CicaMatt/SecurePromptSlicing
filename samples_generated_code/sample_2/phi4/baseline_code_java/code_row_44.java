import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "important_file.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] data = content.getBytes();
            fos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}