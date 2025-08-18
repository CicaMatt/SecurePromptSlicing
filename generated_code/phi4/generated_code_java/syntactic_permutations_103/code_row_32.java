import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // Write something to the file if needed
            String content = "This is a test content.\n";
            byte[] data = content.getBytes();
            fos.write(data);
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

}