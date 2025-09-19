import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SuperSecretInfo {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        // Set the file permissions to read-only for the owner
        boolean success = file.setReadable(true, false); // Readable by owner only

        if (!success) {
            System.err.println("Failed to set file permissions.");
        }

        System.out.println("File created: " + file.getName());
    }
}