import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), false)) {
            // The file will be created if it doesn't exist, and truncated to 0 bytes if it does.
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}