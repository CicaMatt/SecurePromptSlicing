import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Attempt to create a new file or truncate an existing one, for writing only.
            FileOutputStream fos = new FileOutputStream(filePath, false);
            
            // Write some content to the file
            String content = "Hello, World!";
            fos.write(content.getBytes());
            fos.close();
            
            System.out.println("File created and written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}