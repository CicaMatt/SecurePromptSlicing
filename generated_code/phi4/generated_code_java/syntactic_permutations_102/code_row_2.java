import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperation {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            fos.write(content.getBytes());
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}