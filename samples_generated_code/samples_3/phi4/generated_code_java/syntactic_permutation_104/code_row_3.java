import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        String content = ".";

        try (FileOutputStream fos = new FileOutputStream(filePath, true)) {
            fos.write(content.getBytes());
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}