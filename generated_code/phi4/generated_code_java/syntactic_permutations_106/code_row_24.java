import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        // Set permissions: read-only for owner
        boolean success = file.setReadable(true, false);  // Readable by owner
        success &= file.setWritable(false, false);       // Not writable by anyone

        if (success) {
            System.out.println("Super secret info has been written to the file with read-only permissions.");
        } else {
            System.out.println("Failed to set the file permissions correctly.");
        }
    }
}