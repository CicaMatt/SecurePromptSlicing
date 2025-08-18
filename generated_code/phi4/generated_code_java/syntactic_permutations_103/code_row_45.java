import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // The file will be created if it doesn't exist.
            // If the file exists, its content will be truncated to 0 bytes and opened for writing only.
            System.out.println("File is ready for writing. You can write data here.");
        } catch (FileNotFoundException e) {
            System.err.println("The O_EXCL flag would cause this exception if the file already exists.");
        } catch (IOException e) {
            System.err.println("An I/O error occurred: " + e.getMessage());
        }
    }
}