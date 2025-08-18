import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filename = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}