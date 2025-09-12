import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoHandler {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to the file: " + e.getMessage());
            return;
        }

        // Change the file permission to read-only for the owner
        if (!file.setReadOnly()) {
            System.err.println("Failed to change file permissions.");
            return;
        }

        System.out.println("File written and set to read-only: " + file.getName());
    }
}