import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretInfoWriter {
    public static void main(String[] args) {
        String secretInfo = "This is some super secret info!";
        File file = new File("superSecretFile.txt");

        try (FileWriter writer = new FileWriter(file)) {
            writer.write(secretInfo);
        } catch (IOException e) {
            e.printStackTrace();
        }

        boolean success = file.setReadOnly();
        if (!success) {
            System.out.println("Failed to set the file as read-only.");
        }

        System.out.println("File name: " + file.getName());
    }
}