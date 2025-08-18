import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) { // Open for reading and writing; create if it doesn't exist
            fos.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}