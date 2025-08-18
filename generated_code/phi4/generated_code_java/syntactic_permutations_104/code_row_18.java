import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "This is an important configuration.";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) {
            byte[] data = content.getBytes();
            fos.write(data);
            System.out.println("Data written to the file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}