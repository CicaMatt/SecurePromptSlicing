import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "This is an important configuration.";
        
        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            byte[] data = content.getBytes();
            fos.write(data);
        } catch (IOException e) {
            System.err.println("Error occurred while writing to the file: " + e.getMessage());
        }
    }
}