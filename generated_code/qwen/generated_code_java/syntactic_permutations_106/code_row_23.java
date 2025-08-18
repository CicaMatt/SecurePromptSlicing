import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretWriter {
    public static void main(String[] args) {
        String secretInfo = "This is super secret info!";
        File file = new File("secret.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        boolean setReadOnly = file.setReadOnly();
        if (setReadOnly) {
            System.out.println("File permissions changed to read-only.");
        } else {
            System.out.println("Failed to change file permissions.");
        }

        System.out.println("The name of the file is: " + file.getName());
    }
}