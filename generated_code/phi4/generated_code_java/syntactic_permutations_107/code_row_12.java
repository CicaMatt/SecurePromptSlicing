import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;

public class SecretFileHandler {
    public static void main(String[] args) {
        String fileName = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        // Step 1: Create the file and write the string to it
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        // Step 2: Change file permissions to restrictive
        File secretFile = new File(fileName);
        if (!secretFile.setReadable(false) || !secretFile.setWritable(false)) {
            System.err.println("Failed to set restrictive permissions on the file.");
        }

        // Step 3: Attempt to print the file content (should fail due to restricted permissions)
        try {
            String fileContent = Files.readString(secretFile.toPath());
            System.out.println(fileContent);
        } catch (IOException e) {
            System.out.println("Unable to read the file due to restrictive permissions.");
        }
    }
}