import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfo {
    public static void main(String[] args) {
        String superSecretInfo = "This is some super secret info.";
        File file = new File("super_secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(superSecretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing the file: " + e.getMessage());
        }

        boolean success = false;

        if (file.exists()) {
            success = file.setReadOnly();
        }

        if (success) {
            System.out.println("File is set to read-only for the owner.");
        } else {
            System.err.println("Failed to set the file as read-only.");
        }

        System.out.println("The name of the file: " + file.getName());
    }
}