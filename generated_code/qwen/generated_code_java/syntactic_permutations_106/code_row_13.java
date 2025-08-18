import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info.";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        boolean success = file.setReadOnly();
        if (success) {
            System.out.println("File permissions changed to read-only for the owner.");
        } else {
            System.out.println("Failed to change file permissions.");
        }

        System.out.println("File name: " + file.getName());
    }
}