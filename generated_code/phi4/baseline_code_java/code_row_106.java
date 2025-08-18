import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("superSecretInfo.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
        }

        if (!file.setReadable(true, false)) {
            System.err.println("Failed to set read permissions for the owner.");
        }
        
        boolean writable = file.canWrite();
        if (!writable) {
            file.setWritable(false); // Ensuring it is explicitly set to read-only
        }

        if (file.exists()) {
            System.out.println("File name: " + file.getName());
        } else {
            System.err.println("Failed to create the file.");
        }
    }
}