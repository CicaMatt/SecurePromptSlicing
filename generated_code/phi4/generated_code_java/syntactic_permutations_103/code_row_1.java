import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // Create or truncate the file to 0 bytes
            if (!new File(filePath).exists()) {
                System.out.println("Creating a new file: " + filePath);
            } else {
                System.out.println("Truncating the existing file: " + filePath);
            }
            
            // Write data to the file
            String content = "Hello, World!";
            fos.write(content.getBytes());
            
        } catch (IOException e) {
            if (!new File(filePath).exists()) {
                System.err.println("File creation failed because it already exists.");
            } else {
                e.printStackTrace();
            }
        }
    }
}