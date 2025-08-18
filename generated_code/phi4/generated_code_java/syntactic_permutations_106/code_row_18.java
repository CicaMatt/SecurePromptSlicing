import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        // Change file permissions to read-only for the owner
        boolean success = file.setReadable(true, false);  // Owner can read
        success &= file.setWritable(false, false);         // Owner cannot write
        success &= file.setExecutable(false, false);       // Owner cannot execute

        if (success) {
            System.out.println("File permissions changed successfully.");
        } else {
            System.err.println("Failed to change file permissions.");
        }

        System.out.println("File name: " + file.getName());
    }
}