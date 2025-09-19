import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret_info.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }

        if (!file.setReadOnly()) {
            System.err.println("Failed to set the file to read-only");
        }

        System.out.println("Secret info written to: " + file.getName());
    }
}