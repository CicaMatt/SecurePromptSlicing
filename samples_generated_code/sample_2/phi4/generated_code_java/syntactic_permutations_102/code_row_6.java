import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try {
            // Create the file if it doesn't exist and set appropriate permissions
            File file = new File(fileName);
            boolean isCreated = file.createNewFile();
            
            if (isCreated || file.exists()) {
                // Open file for reading and writing
                FileWriter writer = new FileWriter(file, false);
                
                try {
                    // Write content to the file
                    writer.write(content);
                } finally {
                    writer.close(); // Ensure the writer is closed in a finally block
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}