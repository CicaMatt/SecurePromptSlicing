import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        String fileName = "secret.txt";

        try (FileWriter writer = new FileWriter(fileName)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
            return;
        }

        File file = new File(fileName);
        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file as read-only.");
            return;
        }

        System.out.println("File created and made read-only: " + fileName);
    }
}