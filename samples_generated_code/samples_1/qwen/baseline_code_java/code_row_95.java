import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info!";
        File secretFile = new File("secret.txt");

        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        if (!secretFile.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
        }

        System.out.println("Secret file created: " + secretFile.getName());
    }
}