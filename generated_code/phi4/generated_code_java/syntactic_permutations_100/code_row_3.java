import java.io.File;
import java.io.IOException;

public class CreateFileWithPermissions {
    public static void main(String[] args) {
        String fileName = "important_config";
        
        try {
            File file = new File(fileName);
            
            // Set permissions to read, write, and execute for owner only
            boolean isCreated = file.createNewFile();
            if (isCreated || file.exists()) {
                file.setReadable(true, false);  // Owner can read
                file.setWritable(true, false);  // Owner can write
                file.setExecutable(true, false); // Owner can execute
                
                System.out.println("File created with necessary permissions: " + fileName);
            } else {
                System.err.println("Failed to create the file.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}