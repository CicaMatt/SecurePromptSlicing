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
            System.err.println("Error writing to the file: " + e.getMessage());
            return;
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file to read-only.");
            return;
        }

        System.out.println("File created and set to read-only: " + file.getName());
    }
}