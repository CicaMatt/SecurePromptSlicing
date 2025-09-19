import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "important_config.txt";
        String content = "Important configuration data";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            byte[] bytesToWrite = content.getBytes();
            fos.write(bytesToWrite);
            System.out.println("File created and written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}