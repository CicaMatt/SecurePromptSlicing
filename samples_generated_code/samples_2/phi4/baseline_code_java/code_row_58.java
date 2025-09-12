import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {

    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret info.";
        
        // Create a new file with the super secret information
        File file = new File("super_secret_info.txt");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        // Change permissions to read-only for the owner
        boolean success = file.setReadable(true, false);  // Readable by owner only
        if (!success) {
            System.err.println("Failed to set file permissions.");
        }

        // Print the name of the file
        System.out.println("File created: " + file.getName());
    }
}