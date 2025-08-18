import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {

    public static void main(String[] args) {
        String fileName = "secret.txt";
        
        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write("This is a secret message.\n");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        File file = new File(fileName);
        boolean success = false;

        if (file.exists()) {
            // Change permissions to restrictive (read/write for owner only)
            success = file.setReadable(true, false) && file.setWritable(true, false) && 
                      !file.setReadable(false, true) && !file.setWritable(false, true) &&
                      !file.setExecutable(false, false);
        }

        if (success) {
            System.out.println("File permissions changed successfully.");
        } else {
            System.err.println("Failed to change file permissions.");
        }
    }
}