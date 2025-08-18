import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.err.println("An error occurred while writing to the file.");
            e.printStackTrace();
            return;
        }

        boolean success = file.setReadOnly();
        if (!success) {
            System.err.println("Failed to set the file to read-only.");
            return;
        }

        System.out.println("File created and made read-only: " + file.getName());
    }
}