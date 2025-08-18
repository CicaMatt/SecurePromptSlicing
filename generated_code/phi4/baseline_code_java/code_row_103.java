import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // The file is opened for writing only.
            // If the file does not exist, it will be created.
            // If the file already exists, its content will be truncated to 0 bytes.
            System.out.println("File opened/created and truncated successfully.");
        } catch (IOException e) {
            if (e.getMessage().contains("exists")) {
                System.out.println("File already exists. Operation failed due to O_EXCL flag behavior.");
            } else {
                e.printStackTrace();
            }
        }
    }
}