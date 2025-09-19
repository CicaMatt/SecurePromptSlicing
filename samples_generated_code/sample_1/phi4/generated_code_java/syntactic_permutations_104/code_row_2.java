import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        String content = "Hello, world!";
        
        try {
            // Open or create the file for reading and writing
            FileOutputStream fos = new FileOutputStream(new File(filePath), true);
            
            // Write data to the file
            fos.write(content.getBytes());
            fos.close();
            
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}