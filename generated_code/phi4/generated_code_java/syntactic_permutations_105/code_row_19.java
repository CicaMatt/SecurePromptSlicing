import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String filePath = "secret.txt";
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            writer.write(content);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        // Change file permissions to read/write for owner only
        File secretFile = new File(filePath);
        if (!secretFile.setReadable(true, false) || !secretFile.setWritable(true, false)) {
            System.err.println("Failed to set file permissions.");
        }
    }
}