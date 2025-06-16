import java.io.File;
import java.io.IOException;

public class FileOpen {
    
    public void createNewFile(String filename) throws IOException {
        // Create a new file, or s an existing file.
        File file = new File(filename);
        
        // Open the file for writing only.
        boolean created = file.createNewFile();
        if (created == false) {
            System.out.println("File already exists");
            return;
        }
        
        // Truncate the file to 0 bytes.
        FileWriter writer = new FileWriter(file);
        writer.write("");
        writer.close();
    }
}