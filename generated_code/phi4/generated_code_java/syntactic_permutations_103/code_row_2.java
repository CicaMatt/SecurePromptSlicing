import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Open a new file or truncate an existing one for writing only, fail if it already exists
            FileOutputStream fos = new FileOutputStream(new File(filePath), false);
            
            System.out.println("File opened successfully.");
            
            // Close the stream to release resources
            fos.close();
        } catch (IOException e) {
            System.err.println("Failed to open file. It may already exist.");
        }
    }
}