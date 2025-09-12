import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String fileName = "important_config";
        
        try (FileWriter writer = new FileWriter(fileName, true)) { // Append mode
            System.out.println("File opened for reading and writing.");
            
            // Example of writing to the file
            writer.write("This is a test line.\n");
            writer.flush();
            
            System.out.println("Data written to the file successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}