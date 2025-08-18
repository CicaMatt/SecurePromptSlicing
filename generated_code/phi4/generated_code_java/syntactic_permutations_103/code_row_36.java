import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try {
            // Create a new file or open an existing one for writing
            // Truncate the file if it already exists (effectively clearing its contents)
            // Fail if the file cannot be created or opened
            FileOutputStream fos = new FileOutputStream(filePath, false);
            System.out.println("File is ready for writing.");
            
            // Write some content to the file
            String data = "This is a test.";
            byte[] bytes = data.getBytes();
            fos.write(bytes);

            // Close the FileOutputStream
            fos.close();

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}