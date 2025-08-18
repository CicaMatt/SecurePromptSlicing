import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(new File(filePath), true)) {
            String content = "Hello, world!";
            byte[] data = content.getBytes();
            
            // Write to the file
            fos.write(data);
            System.out.println("Data written successfully.");
            
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}