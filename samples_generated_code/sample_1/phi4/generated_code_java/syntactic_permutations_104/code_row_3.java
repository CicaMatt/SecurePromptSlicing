import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "Important Configuration Data";

        try (FileOutputStream fos = new FileOutputStream(new File(fileName), true)) {
            fos.write(content.getBytes());
            System.out.println("Data written to file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}