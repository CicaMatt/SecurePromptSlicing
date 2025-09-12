import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "This is important configuration data.";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            fos.write(content.getBytes());
            System.out.println("Content written to file: " + fileName);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}