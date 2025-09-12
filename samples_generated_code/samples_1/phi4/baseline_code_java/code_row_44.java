import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            byte[] bytes = content.getBytes();
            fos.write(bytes);
            System.out.println("Content written to the file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}