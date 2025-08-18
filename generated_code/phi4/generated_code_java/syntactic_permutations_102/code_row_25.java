import java.io.FileOutputStream;
import java.io.IOException;

public class ImportantConfigHandler {
    public static void main(String[] args) {
        String filePath = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(contentToWrite.getBytes());
            System.out.println("Content written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}