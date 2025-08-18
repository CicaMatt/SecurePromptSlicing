import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String contentToWrite = "Important configuration data";

        openAndWriteToFile(filePath, contentToWrite);
    }

    private static void openAndWriteToFile(String filePath, String content) {
        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            byte[] bytesToWrite = content.getBytes();
            fos.write(bytesToWrite);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}