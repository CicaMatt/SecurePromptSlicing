import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFileExample {
    public static void main(String[] args) {
        String filename = "example.txt";

        File file = new File(filename);
        
        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            // This will create the file or truncate it if it exists
            System.out.println("File opened successfully for writing.");
        } catch (IOException e) {
            System.err.println("Error occurred: " + e.getMessage());
        }
    }
}