import java.io.FileOutputStream;
import java.io.IOException;

public class FileWriteExample {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}