import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "This is the important configuration.";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) { // O_RDWR + O_CREAT
            byte[] data = content.getBytes();
            fos.write(data);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}