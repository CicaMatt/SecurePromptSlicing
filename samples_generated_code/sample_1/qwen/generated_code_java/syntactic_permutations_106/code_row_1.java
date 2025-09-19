import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
            System.out.println("File created and written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file: " + e.getMessage());
            return;
        }

        boolean isReadOnlySet = file.setReadOnly();
        if (isReadOnlySet) {
            System.out.println("File permissions changed to read-only for the owner.");
        } else {
            System.err.println("Failed to change file permissions.");
        }

        System.out.println("The name of the file is: " + file.getName());
    }
}